#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    cv::Mat img;

    if (argc >= 2) {
        // load image from file
        img = cv::imread(argv[1], cv::IMREAD_COLOR);
        if (img.empty()) {
            std::cerr << "Failed to load image: " << argv[1] << "\n";
            return 1;
        }
    } else {
        // open default camera
        cv::VideoCapture cap(0);
        if (!cap.isOpened()) {
            std::cerr << "Could not open camera and no image provided.\n";
            return 2;
        }
        cap >> img;
        if (img.empty()) {
            std::cerr << "Captured empty frame from camera.\n";
            return 3;
        }
    }

    // convert to grayscale
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // show windows
    cv::imshow("Original", img);
    cv::imshow("Gray", gray);

    // save grayscale result
    const std::string outName = "gray_result.png";
    if (!cv::imwrite(outName, gray)) {
        std::cerr << "Failed to write " << outName << "\n";
    } else {
        std::cout << "Saved " << outName << "\n";
    }

    std::cout << "Press any key in one of the image windows to exit...\n";
    cv::waitKey(0);
    return 0;
}
