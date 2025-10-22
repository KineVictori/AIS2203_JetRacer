
#include <opencv2/opencv.hpp>
#include "vision/Vision.hpp"



int main() {

    Vision vision;

    while(true) {
        vision.update();
        auto frame = vision.getFrame();
        if(frame.empty()) break;
        cv::imshow("CSI Camera", frame);
        if(cv::waitKey(1) == 27) break; // ESC to exit
    }
    return 0;
}