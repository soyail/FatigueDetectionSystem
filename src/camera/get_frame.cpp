#include <camera/get_frame.h>

GetFrame::GetFrame(std::queue<cv::Mat> *frame_contain, std::mutex *frame_contain_lock,
        const int _skip_interval):
        _frame_contain_lock(frame_contain_lock),
        _frame_contain(frame_contain),
        _skip_interval(_skip_interval) {
}

/**
 * 将frame放入contain
 * @param frame
 */
void GetFrame::putFrame2Contain(const cv::Mat &frame) {
    this->_frame_contain_lock->lock();
    this->_frame_contain->push(frame);
    // 队列最大长度需要为2 以下行确保获取队列中存储的都是最新图像
    if (this->_frame_contain->size() > 1) {
        this->_frame_contain->pop();
        this->_frame_contain_lock->unlock();
    }
    else {
        this->_frame_contain_lock->unlock();
        sleep(1);
    }
}

/**
 * 关闭摄像头
 * @param cap
 */
void GetFrame::shutdownCamera(cv::VideoCapture &cap) {
    cap.release();
}

/**
 * 重新拉流
 * @param cap
 * @param camera_id
 */
void GetFrame::restartCamera(cv::VideoCapture &cap, int camera_id) {
    std::cout << "[INFO] 正在重新拉流" << std::endl;
    this->shutdownCamera(cap);
    cap.open(camera_id);
}

/**
 * 开始读取图片
 * @param camera_id
 */
void GetFrame::beginReadCamera(int camera_id) {
    int frame_idx = 0;
    int failed_times = 0;
    cv::VideoCapture cap(camera_id);
    if (!cap.isOpened()) {
        throw "[error] 视频流无法正常打开！";
        exit(-1);
    }
    while (true) {
        cv::Mat frame;
        cap >> frame;
        // 获取图像失败
        if (frame.empty()) {
            frame_idx = 0;
            failed_times++;
            std::cout << "[INFO] 获取图像失败" << failed_times << "次" << std::endl;
            this->restartCamera(cap, camera_id);
            if (failed_times == 3) break;
            continue;
        }
        // 跳帧
        frame_idx++;
        if (frame_idx % this->_skip_interval != 0) continue;
        this->putFrame2Contain(frame);
    }
    this->shutdownCamera(cap);
}

