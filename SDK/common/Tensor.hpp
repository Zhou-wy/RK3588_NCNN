//
// Created by zhouwy on 2023/11/11.
//

#ifndef RK3588_NCNN_TENSOR_HPP
#define RK3588_NCNN_TENSOR_HPP

#include <iostream>
#include <memory>
#include <vector>


namespace NCN {
    enum class DataType : int {
        Float = 0,
        Float16 = 1,
        Int32 = 2,
        UInt8 = 3
    };

    using float16 = unsigned short;

    int data_type_size(DataType dt);

    const char *data_type_string(DataType dt);

    class MgtMem {
    public:
        MgtMem() = default;

        MgtMem(void *cpu, size_t cpu_size);

        virtual ~MgtMem();

        void *cpu(size_t size);

        void release_cpu();

        inline size_t cpu_size() const { return m_cpu_size; }

        inline void *cpu() const { return m_cpu; }

        void reference_data(void *cpu, size_t cpu_size);

    private:
        void *m_cpu = nullptr;
        size_t m_cpu_size = 0;
    };

    class Tensor {
    public:
        Tensor(const Tensor &other) = delete;

        Tensor &operator=(const Tensor &other) = delete;

        explicit Tensor(DataType d_type = DataType::Float, std::shared_ptr<MgtMem> data = nullptr);

        explicit Tensor(int n, int c, int h, int w, DataType d_type = DataType::Float,
                        std::shared_ptr<MgtMem> data = nullptr);

        explicit Tensor(int n_dims, const int *dims, DataType d_type = DataType::Float,
                        std::shared_ptr<MgtMem> data = nullptr);

        explicit Tensor(const std::vector<int> &dims, DataType d_type = DataType::Float,
                        std::shared_ptr<MgtMem> data = nullptr);

        virtual ~Tensor();

        int numel() const;

        inline int ndims() const { return this->m_shape.size(); }

        inline int size(int index) const { return this->m_shape[index]; }

        inline int shape(int index) const { return this->m_shape[index]; }

        inline int batch() const { return this->m_shape[0]; }

        inline int channel() const { return this->m_shape[1]; }

        inline int height() const { return this->m_shape[2]; }

        inline int width() const { return this->m_shape[3]; }

        inline DataType type() const { return this->m_type; }

        inline const std::vector<int> &dims() const { return this->m_shape; }

        inline const std::vector<size_t> &strides() const { return this->m_strides; }

        inline int bytes() const { return this->m_bytes; }

        inline int bytes(int start_axis) const { return count(start_axis) * element_size(); }

        inline int element_size() const { return data_type_size(this->m_type); }

        std::shared_ptr<Tensor> clone() const;

        Tensor &release();

        Tensor &set_to(float value);

        bool empty() const;

        template<typename... _Args>
        int offset(int index, _Args... index_args) const {
            const int index_array[] = {index, index_args...};
            return offset_array(sizeof...(index_args) + 1, index_array);
        }

        int offset_array(const std::vector<int> &index) const;

        int offset_array(size_t size, const int *index_array) const;

        template<typename... _Args>
        Tensor &resize(int dim_size, _Args... dim_size_args) {
            const int dim_size_array[] = {dim_size, dim_size_args...};
            return resize(sizeof...(dim_size_args) + 1, dim_size_array);
        }

        Tensor &resize(int ndims, const int *dims);

        Tensor &resize(const std::vector<int> &dims);

        Tensor &resize_single_dim(int idim, int size);

        int count(int start_axis = 0) const;

        Tensor &to_half();

        Tensor &to_float();

        inline void *cpu() const {
            m_data->cpu(m_bytes);
            return m_data->cpu();
        }

        template<typename DType>
        inline const DType *cpu() const { return (DType *) cpu(); }

        template<typename DType>
        inline DType *cpu() { return (DType *) cpu(); }

        template<typename DType, typename... _Args>
        inline DType *cpu(int i, _Args &&...args) { return cpu<DType>() + offset(i, args...); }

        template<typename DType, typename... _Args>
        inline DType &at(int i, _Args &&...args) { return *(cpu<DType>() + offset(i, args...)); }

        std::shared_ptr<MgtMem> get_data() const { return m_data; }

//        Tensor &set_mat(int n, const cv::Mat &image);
//        Tensor &set_norm_mat(int n, const cv::Mat &image, float mean[3], float std[3]);
//        cv::Mat at_mat(int n = 0, int c = 0) { return cv::Mat(height(), width(), CV_32F, cpu<float>(n, c)); }
        const char *shape_string() const { return m_shape_string; }

        const char *descriptor() const;

        void reference_data(const std::vector<int> &shape, void *cpu_data, size_t cpu_size, DataType d_type);

    private:
        Tensor &compute_shape_string();

        Tensor &adajust_memory_by_update_dims_or_type();

        void setup_data(std::shared_ptr<MgtMem> data);

    private:
        std::vector<int> m_shape;
        std::vector<size_t> m_strides;
        size_t m_bytes = 0;
        DataType m_type = DataType::Float;
        char m_shape_string[100];
        char m_descriptor_string[100];
        std::shared_ptr<MgtMem> m_data;
    };
};
#endif //RK3588_NCNN_TENSOR_HPP
