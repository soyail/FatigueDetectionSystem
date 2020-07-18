//
// Created by 李陆沁 on 2020/7/18.
//

#ifndef FATIGUEDETECTIONSYSTEM_GET_FRAME_H
#define FATIGUEDETECTIONSYSTEM_GET_FRAME_H

#include <queue>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include "opencv2/opencv.hpp"

class GetFrame {
public:

    GetFrame(std::queue<cv::Mat> *frame_contain, std::mutex *frame_contain_lock,
            const int _skip_interval);
    void beginReadCamera(int camera_id=0);
    void putFrame2Contain(const cv::Mat &frame);
    void shutdownCamera(cv::VideoCapture &cap);
    void restartCamera(cv::VideoCapture &cap, int camera_id);

private:
    // 视频帧容器
    std::queue<cv::Mat> *_frame_contain;
    // 容器锁
    std::mutex *_frame_contain_lock;
    // 跳帧频率
    int _skip_interval;
};


#endif //FATIGUEDETECTIONSYSTEM_GET_FRAME_H
