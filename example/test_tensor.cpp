//
// Created by zhouwy on 2023/11/13.
//

#include "../SDK/common/Tensor.hpp"
#include <iostream>

union FloatConverter {
    float float32;
    uint16_t float16[2];
};

bool isFloat16(float value) {
    FloatConverter converter;
    converter.float32 = value;

    // 检查指数部分是否在 float16 能表示的范围内
    uint16_t exponent = (converter.float16[1] & 0x7C00) >> 10;
    return exponent >= 1 && exponent <= 30;
}

int main(int argc, char *argv[]) {
    NCN::Tensor tensor(2, 3, 4, 5, NCN::DataType::Float);
    tensor.set_to(1);

    std::cout << "tensor.ndims = " << tensor.ndims() << std::endl;
    std::cout << "tensor.size_0 = " << tensor.size(0) << std::endl;
    std::cout << "tensor.size_1 = " << tensor.size(1) << std::endl;
    std::cout << "tensor.size_2 = " << tensor.size(2) << std::endl;
    std::cout << "tensor.size_3 = " << tensor.size(3) << std::endl;
    std::cout << "data type = " << data_type_string(tensor.type()) << std::endl;
    tensor.at<float>(0, 0) = 24.0;
    std::cout << "tensor.at<float>(0, 0) = " << tensor.at<float>(0, 0)
              << std::endl;
    std::cout << tensor.element_size() << "==" << sizeof(float) << std::endl;
    std::cout << tensor.bytes() << "==" << 2 * 3 * 4 * 5 * sizeof(float)
              << std::endl;
    if (isFloat16(tensor.at<float>(0, 0, 0, 0))) {
        std::cout << "The float value is float16." << std::endl;
    } else {
        std::cout << "The float value is float32." << std::endl;
    }

    tensor.resize({1, 6, 4, 5});
    std::cout << "resized tensor.shape(0) = " << tensor.shape(0) << std::endl;
    std::cout << "resized tensor.batch() = " << tensor.batch() << std::endl;
    std::cout << "resized tensor.channel = " << tensor.channel() << std::endl;
    std::cout << "resized tensor.height = " << tensor.height() << std::endl;
    std::cout << "resized tensor.width = " << tensor.width() << std::endl;
    std::cout << "resized tensor.at<float>(0, 0) = "
              << typeid(tensor.at<float>(0, 0, 0, 0)).name() << std::endl;

    tensor.to_half();
    std::cout << "resized tensor type = " << data_type_string(tensor.type())
              << std::endl;
    if (isFloat16(tensor.at<float>(0, 0, 0, 0))) {
        std::cout << "The float value is float16." << std::endl;
    } else {
        std::cout << "The float value is float32." << std::endl;
    }
    return 0;
}
