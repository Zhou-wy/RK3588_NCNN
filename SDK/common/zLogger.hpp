//
// Created by zhouwy on 2023/11/14.
//

#ifndef RK3588_NCNN_ZLOGGER_HPP
#define RK3588_NCNN_ZLOGGER_HPP
#include <iostream>
#include <vector>
#include <tuple>
#include <ctime>

#if defined(_WIN32)
#define U_OS_WINDOWS
#elif defined(__APPLE__)
#define U_OS_MACOS
#else
#define U_OS_LINUX
#endif


#define zDebug(...) NCN::__log_func(__FILE__, __LINE__, NCN::LogLevel::Debug, __VA_ARGS__)
#define zVerbose(...) NCN::__log_func(__FILE__, __LINE__, NCN::LogLevel::Verbose, __VA_ARGS__)
#define zInfo(...) NCN::__log_func(__FILE__, __LINE__, NCN::LogLevel::Info, __VA_ARGS__)
#define zWarning(...) NCN::__log_func(__FILE__, __LINE__, NCN::LogLevel::Warning, __VA_ARGS__)
#define zError(...) NCN::__log_func(__FILE__, __LINE__, NCN::LogLevel::Error, __VA_ARGS__)
#define zFatal(...) NCN::__log_func(__FILE__, __LINE__, NCN::LogLevel::Fatal, __VA_ARGS__)

namespace NCN
{

    using namespace std;

    enum class LogLevel : int
    {
        Debug = 5,
        Verbose = 4,
        Info = 3,
        Warning = 2,
        Error = 1,
        Fatal = 0
    };


    std::string date_now();
    std::string time_now();
    std::string gmtime_now();
    std::string gmtime(time_t t);
    time_t gmtime2ctime(const std::string &gmt);
    void sleep(int ms);

    bool isfile(const std::string &file);
    bool mkdir(const std::string &path);
    bool mkdirs(const std::string &path);
    bool delete_file(const std::string &path);
    bool rmtree(const std::string &directory, bool ignore_fail = false);
    bool exists(const std::string &path);
    std::string format(const char *fmt, ...);
    FILE *fopen_mkdirs(const std::string &path, const std::string &mode);
    std::string file_name(const std::string &path, bool include_suffix = true);
    std::string directory(const std::string &path);
    long long timestamp_now();
    double timestamp_now_float();
    time_t last_modify(const std::string &file);
    std::vector<uint8_t> load_file(const std::string &file);
    std::string load_text_file(const std::string &file);
    size_t file_size(const std::string &file);

    bool begin_with(const std::string &str, const std::string &with);
    bool end_with(const std::string &str, const std::string &with);
    std::vector<std::string> split_string(const std::string &str, const std::string &spstr);
    std::string replace_string(const std::string &str, const std::string &token, const std::string &value, int nreplace = -1, int *out_num_replace = nullptr);

    // h[0-1], s[0-1], v[0-1]
    // return, 0-255, 0-255, 0-255
    std::tuple<uint8_t, uint8_t, uint8_t> hsv2rgb(float h, float s, float v);
    std::tuple<uint8_t, uint8_t, uint8_t> random_color(int id);

    //   abcdefg.pnga          *.png      > false
    //   abcdefg.png           *.png      > true
    //   abcdefg.png          a?cdefg.png > true
    bool pattern_match(const char *str, const char *matcher, bool igrnoe_case = true);
    std::vector<std::string> find_files(
            const std::string &directory,
            const std::string &filter = "*", bool findDirectory = false, bool includeSubDirectory = false);

    std::string align_blank(const std::string &input, int align_size, char blank = ' ');
    bool save_file(const std::string &file, const std::vector<uint8_t> &data, bool mk_dirs = true);
    bool save_file(const std::string &file, const std::string &data, bool mk_dirs = true);
    bool save_file(const std::string &file, const void *data, size_t length, bool mk_dirs = true);

    // 捕获：SIGINT(2)、SIGQUIT(3)
    int while_loop();

    // 关于logger的api
    const char *level_string(LogLevel level);
    void set_logger_save_directory(const std::string &loggerDirectory);

    void set_log_level(LogLevel level);
    LogLevel get_log_level();
    void __log_func(const char *file, int line, LogLevel level, const char *fmt, ...);
    void destroy_logger();

    std::vector<uint8_t> base64_decode(const std::string &base64);
    std::string base64_encode(const void *data, size_t size);

    inline int upbound(int n, int align = 32) { return (n + align - 1) / align * align; }
    std::string join_dims(const std::vector<int64_t> &dims);
};

#endif //RK3588_NCNN_ZLOGGER_HPP
