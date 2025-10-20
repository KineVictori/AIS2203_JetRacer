

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::string pipeline = "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=1280, height=720, framerate=30/1 ! "
                           "nvvidconv ! videoconvert ! appsink";
    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    if(!cap.isOpened()) {
        std::cerr << "Failed to open CSI camera\n";
        return -1;
    }
    cv::Mat frame;
    while(true) {
        cap >> frame;
        if(frame.empty()) break;
        imshow("CSI Camera", frame);
        if(cv::waitKey(1) == 27) break; // ESC to exit
    }
    return 0;
}