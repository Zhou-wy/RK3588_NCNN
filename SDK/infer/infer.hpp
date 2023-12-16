//
// Created by zhouwy on 2023/11/11.
//

#ifndef RK3588_NCNN_INFER_HPP
#define RK3588_NCNN_INFER_HPP


class infer {

    infer() = default;
    virtual void pre_process();
    virtual void post_process();

    virtual ~infer();
};

class inferInstance : public infer{
public:
    inferInstance();
    void pre_process() override;
    void post_process() override;

    ~inferInstance();
private:
    
};

#endif //RK3588_NCNN_INFER_HPP
