//
// Created by zhouwy on 2023/11/11.
//

#include "Tensor.hpp"
#include <cstring>
#include <cstdint>
namespace NCN {
    MgtMem::MgtMem(void *cpu, size_t cpu_size) {
        reference_data(cpu, cpu_size);
    }

    MgtMem::~MgtMem() {
        release_cpu();
    }

    void *MgtMem::cpu(size_t size) {
        if (m_cpu_size < size) {
            release_cpu();

            m_cpu_size = size;
            m_cpu = malloc(m_cpu_size);
            memset(m_cpu, 0, m_cpu_size);
        }
        return m_cpu;
    }

    void MgtMem::release_cpu() {
        if (m_cpu) {
            m_cpu = nullptr;
        }
        m_cpu_size = 0;
    }

    void MgtMem::reference_data(void *cpu, size_t cpu_size) {
        release_cpu();

        if (m_cpu == nullptr || m_cpu_size == 0) {
            cpu = nullptr;
            cpu_size = 0;
        }
        this->m_cpu = cpu;
        this->m_cpu_size = cpu_size;
    }

    Tensor::Tensor(DataType d_type, std::shared_ptr<MgtMem> data) {
        this->m_type = d_type;
        this->m_descriptor_string[0] = 0;
        setup_data(data);

    }

    Tensor::Tensor(int n, int c, int h, int w, DataType d_type, std::shared_ptr<MgtMem> data) {
        this->m_type = d_type;
        this->m_descriptor_string[0] = 0;
        setup_data(data);
        resize(n, c, h, w);

    }

    Tensor::Tensor(int n_dims, const int *dims, DataType d_type, std::shared_ptr<MgtMem> data) {
        this->m_type = d_type;
        this->m_descriptor_string[0] = 0;
        setup_data(data);
        resize(n_dims, dims);
    }

    Tensor::Tensor(const std::vector<int> &dims, DataType d_type, std::shared_ptr<MgtMem> data) {
        this->m_type = d_type;
        m_descriptor_string[0] = 0;
        setup_data(data);
        resize(dims);
    }

    Tensor::~Tensor() {
        release();
    }

    int Tensor::numel() const {
        int value = m_shape.empty() ? 0 : 1;
        for (int i: m_shape) {
            value *= i;
        }
        return value;
    }

    std::shared_ptr<Tensor> Tensor::clone() const {
        auto new_tensor = std::make_shared<Tensor>(m_shape, m_type);
        memcpy(new_tensor->cpu(), this->cpu(), this->m_bytes);
        return new_tensor;
    }

    Tensor &Tensor::release() {
        m_data->release_cpu();
        m_shape.clear();
        m_bytes = 0;
        return *this;
    }

    template<typename T>
    static inline void memset_any_type(T *ptr, size_t count, T value) {
        for (size_t i = 0; i < count; ++i)
            *ptr++ = value;
    }

    float float16_to_float(float16 value) {
        // Extract components from float16 representation
        std::uint16_t sign = (value >> 15) & 0x1;
        std::uint16_t exponent = (value >> 10) & 0x1F;
        std::uint16_t significand = value & 0x3FF;

        // Bias the exponent
        exponent = static_cast<std::uint16_t>(exponent - 15 + 127);

        // Create the IEEE 754 format
        std::uint32_t floatBits = (sign << 31) | (exponent << 23) | (significand << 13);

        // Convert the bit pattern to a float
        return *reinterpret_cast<float*>(&floatBits);
    }


    float16 float_to_float16(float value) {
        // Extract components of the IEEE 754 format
        std::uint32_t floatBits = *reinterpret_cast<std::uint32_t*>(&value);
        std::uint16_t sign = (floatBits >> 31) & 0x1;
        std::uint16_t exponent = (floatBits >> 23) & 0xFF;
        std::uint32_t significand = floatBits & 0x7FFFFF;

        // Bias the exponent and round to the nearest representable value
        exponent = static_cast<std::uint16_t>(exponent + 127 - 15 + (significand > 0x7FFFFF));

        // Clamp the exponent to avoid overflow
        if (exponent > 0x1F) {
            exponent = 0x1F;
        }
        // Create the float16 representation
        return (sign << 15) | (exponent << 10) | ((significand >> 13) & 0x3FF);
    }

    Tensor &Tensor::set_to(float value) {
        int c = count();
        if (m_type == DataType::Float) {
            memset_any_type(cpu<float>(), c, value);
        } else if (m_type == DataType::Float16) {
            memset_any_type(cpu<float16>(), c, float_to_float16(value));
        } else if (m_type == DataType::Int32) {
            memset_any_type(cpu<int>(), c, (int) value);
        } else if (m_type == DataType::UInt8) {
            memset_any_type(cpu<uint8_t>(), c, (uint8_t) value);
        } else {
//            INFOE("Unsupport type: %d", m_type);
        }
        return *this;
    }

    bool Tensor::empty() const {
        return m_data->cpu() == nullptr;
    }

    int Tensor::offset_array(const std::vector<int> &index) const {
        return offset_array(index.size(), index.data());
    }

    int Tensor::offset_array(size_t size, const int *index_array) const {
//        Assert(size <= m_shape.size());
        int value = 0;
        for (int i = 0; i < m_shape.size(); ++i)
        {

            if (i < size)
                value += index_array[i];

            if (i + 1 < m_shape.size())
                value *= m_shape[i + 1];
        }
        return 0;
    }

    Tensor &Tensor::resize(int ndims, const int *dims) {
        std::vector<int> setup_dims(ndims);
        for (int i = 0 ; i < ndims; i++) {
            int dim = dims[i];
            if (dim == -1){
                dim = m_shape[i];
            }
            setup_dims[i] = dim;
        }
        this->m_shape = setup_dims;
        this->m_strides.resize(setup_dims.size());

        size_t prev_size = element_size();
        size_t prev_shape = 1;
        for (int i = (int) m_strides.size() -1; i >= 0; --i){
            if (i + 1 < m_strides.size())
            {
                prev_size = m_strides[i + 1];
                prev_shape = m_shape[i + 1];
            }
            m_strides[i] = prev_size * prev_shape;
        }

        return *this;
    }

    Tensor &Tensor::resize(const std::vector<int> &dims) {
        return <#initializer#>;
    }

    Tensor &Tensor::resize_single_dim(int idim, int size) {
        return <#initializer#>;
    }

    int Tensor::count(int start_axis) const {
        return 0;
    }

    Tensor &Tensor::to_half() {
        return <#initializer#>;
    }

    Tensor &Tensor::to_float() {
        return <#initializer#>;
    }

    Tensor &Tensor::to_cpu(bool copy) {
        return <#initializer#>;
    }

    const char *Tensor::descriptor() const {
        return nullptr;
    }

    void Tensor::reference_data(const std::vector<int> &shape, void *cpu_data,
                                size_t cpu_size, void *gpu_data,
                                size_t gpu_size, DataType d_type) {

    }

    Tensor &Tensor::compute_shape_string() {
        return <#initializer#>;
    }

    Tensor &Tensor::adajust_memory_by_update_dims_or_type() {
        return <#initializer#>;
    }

    void Tensor::setup_data(std::shared_ptr<MgtMem> data) {

    }
};