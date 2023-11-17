//
// Created by zhouwy on 2023/11/11.
//

#ifndef RK3588_NCNN_INFER_HPP
#define RK3588_NCNN_INFER_HPP


class infer {
public:
    infer() = delete; // 纯虚类禁用默认构造
    infer(infer &) = delete; // 纯虚类禁用拷贝构造
    infer &operator=(infer &other) = delete; // 纯虚类禁用赋值

    virtual void pre_process();
    virtual void post_process();

    virtual ~infer();
};

#endif //RK3588_NCNN_INFER_HPP
