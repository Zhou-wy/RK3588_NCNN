//
// Created by zhouwy on 2023/11/16.
//
#include <iostream>
#include <ctime>
#include <tuple>
#include <vector>
#include <cstdio>
#include "../SDK/common/zLogger.hpp"
// Include other necessary headers for your functions
using namespace NCN;

int main()
{
    // Test date and time functions
    std::string current_date = date_now();
    std::string current_time = time_now();
    std::string gm_time = gmtime_now();

    zInfo("Current Date: %s", current_date.c_str());
    zInfo("Current Time:%s", current_time.c_str());
    zInfo("GMT Time: %s", gm_time.c_str());

    // Test file-related functions
    std::string test_file = "apple_bin/test_dir/test.txt";
    std::string test_directory = "apple_bin/test_dir";

    // Test isfile function
    bool is_file = isfile(test_file);
    std::cout << "Is file '" << test_file << "' present? " << std::boolalpha << is_file << std::endl;

    // Test mkdir function
    bool mkdir_result = mkdir(test_directory);
    std::cout << "Create directory '" << test_directory << "' result: " << std::boolalpha << mkdir_result << std::endl;

    // Test delete_file function
    bool delete_file_result = delete_file(test_file);
    std::cout << "Delete file '" << test_file << "' result: " << std::boolalpha << delete_file_result << std::endl;

    // Test rmtree function
    bool rmtree_result = rmtree(test_directory);
    std::cout << "Remove directory '" << test_directory << "' result: " << std::boolalpha << rmtree_result << std::endl;

    // Test other functions

    // Test format function
    std::string formatted_str = format("Test %d %s", 42, "format");
    std::cout << "Formatted String: " << formatted_str << std::endl;

    // Test fopen_mkdirs function
    FILE *file = fopen_mkdirs("apple_bin/test_dir/test_file.txt", "w");
    if (file != nullptr)
    {
        fputs("Hello, fopen_mkdirs!", file);
        fclose(file);
        std::cout << "File created using fopen_mkdirs." << std::endl;
    }
    else
    {
        std::cerr << "Error creating file using fopen_mkdirs." << std::endl;
    }

    // Test file_name and directory functions
    std::string file_name_result = file_name("/Users/zwy/CppProject/RK3588_NCNN/apple_bin/test_dir/test_file.txt");
    std::string directory_result = directory("/Users/zwy/CppProject/RK3588_NCNN/apple_bin/test_dir/test_file.txt");
    std::cout << "File Name: " << file_name_result << std::endl;
    std::cout << "Directory: " << directory_result << std::endl;

    // Test timestamp functions
    long long timestamp = timestamp_now();
    double timestamp_float = timestamp_now_float();
    std::cout << "Timestamp (long long): " << timestamp << std::endl;
    std::cout << "Timestamp (float): " << timestamp_float << std::endl;

    // Test sleep function
    sleep(2000); // Sleep for 2000 milliseconds

    return 0;
}
