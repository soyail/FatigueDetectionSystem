#include <thread>
#include "camera/get_frame.h"

void getFrame(std::queue<cv::Mat> *frame_containt, std::mutex *frame_containt_lock) {
    GetFrame camera(frame_containt, frame_containt_lock, 1);
    camera.beginReadCamera(0);
}

int main() {
    // 测试摄像头
    std::queue<cv::Mat> frame_containt;
    std::mutex frame_containt_lock;
    std::thread getFrameThread(getFrame, &frame_containt, &frame_containt_lock);

    while (true) {
        if (!frame_containt.empty()) {
            frame_containt_lock.lock();
            cv::Mat frame = frame_containt.front();
            frame_containt_lock.unlock();
            cv::imshow("test", frame);
            cv::waitKey(1);
        }
    }
}

