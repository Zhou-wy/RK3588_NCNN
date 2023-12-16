#include <iostream>

#include "SDK/common/Tensor.hpp"
#include "SDK/common/zLogger.hpp"


int main() {
    // std::cout << "Hello, World!" << std::endl;
    NCN::Tensor tensor(2, 3, 4, 5, NCN::DataType::Float);
    tensor.set_to(1);

    zInfo("Hello World");
    zWarning("Hello warning");

    return 0;
}
