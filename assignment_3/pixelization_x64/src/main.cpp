
#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>


void printImage(cv::Mat img) {
    static std::vector<cv::Mat> images;

    cv::imshow("Pixelated Image", img);
    cv::waitKey(30);
}

void pixelateBlock(cv::Mat& img, cv::Rect rect) {
    cv::Mat block = img(rect);
    cv::Scalar color = mean(block);
    block.setTo(color);
}

void pixelateImage(cv::Mat& img, int squareSize, int numThreads = 1) {
    std::vector<std::thread> threads;
    int blockHeight = img.rows / numThreads;

    for (int i = 0; i < numThreads; i++) {
        int startY = i * blockHeight;
        int endY = (i + 1) * blockHeight;

        threads.emplace_back([=, &img]() {
            for (int y = startY; y < endY; y += squareSize) {
                for (int x = 0; x < img.cols; x += squareSize) {
                    cv::Rect rect = cv::Rect(x, y, squareSize, squareSize) & cv::Rect(0, 0, img.cols, endY);
                    pixelateBlock(img, rect);
                    printImage(img);
                }
            }
            });
    }

    for (auto& t : threads) {
        t.join();
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <image_path> <square_size> <mode>" << std::endl;
        return -1;
    }

    std::string temps = argv[1];
    int squareSize = std::stoi(argv[2]);

    cv::Mat image = cv::imread(temps);
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    temps = argv[3];
    int numThreads = std::thread::hardware_concurrency();
    if (!numThreads || temps == "S") numThreads = 1; // Fallback to single thread if hardware_concurrency returns 0 or it is single mode
    std::cout << "Number of threads: " << numThreads << std::endl;

    cv::namedWindow("Pixelated Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("Pixelated Image", 800, 600);

    cv::Mat pixelatedImage = image.clone();
    pixelateImage(pixelatedImage, squareSize, numThreads);

    cv::imshow("Pixelated Image", pixelatedImage);
    cv::waitKey(0);

    return 0;
}