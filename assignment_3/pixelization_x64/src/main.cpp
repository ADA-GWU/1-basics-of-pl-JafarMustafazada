#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>

static bool flag1 = true;
static bool flag2 = true;

void processBlock(cv::Mat& image, int blockSize, int startRow, int endRow) {
	cv::Rect wholeBlock(0, 0, image.cols, endRow);

	for (int y = startRow; y < endRow; y += blockSize) {
		for (int x = 0; x < image.cols; x += blockSize) {
			cv::Rect blockRect = cv::Rect(x, y, blockSize, blockSize) & wholeBlock;
			cv::Mat block = image(blockRect);
			cv::Scalar avgColor = cv::mean(block);
			block.setTo(avgColor);

			while (flag2) std::this_thread::sleep_for(std::chrono::milliseconds(1));
			flag2 = true;
		}
	}
}

void pixelateWithAnimation(cv::Mat& image, int blockSize, int threadCount) {
	int blocksInRow = (image.rows + blockSize - 1) / blockSize;
	int blocksPerThread = (blocksInRow + threadCount - 1) / threadCount;
	int rowsPerThread = blocksPerThread * blockSize;

	std::thread** threads = new std::thread * [threadCount];

	for (int i = 0; i < threadCount; i++) {
		int startRow = i * rowsPerThread;
		int endRow = std::min(startRow + rowsPerThread, image.rows);
		threads[i] = new std::thread(processBlock, std::ref(image), blockSize, startRow, endRow);
	}

	for (int i = 0; i < threadCount; i++) {
		std::thread& t = *threads[i];
		t.join();
	}

	flag1 = false;
	delete[] threads;
}


int main(int argc, char** argv) {
	if (argc < 4) {
		std::cerr << "Usage: " << argv[0] << " <image_path> <square_size> <mode> <delay_inms>" << std::endl;
		return -1;
	}

	std::string temps = argv[1];
	cv::Mat image = cv::imread(temps);
	int delayms = 30;
	int blockSize = std::stoi(argv[2]);
	int numThreads = std::thread::hardware_concurrency();
	temps = argv[3];

	if (argc > 4) delayms = std::stoi(argv[4]);
	if (image.empty()) {
		std::cerr << "Could not open or find the image!" << std::endl;
		return -1;
	}
	if (!numThreads || temps == "S") numThreads = 1;

	std::cout << "\nNumber of threads: " << numThreads << std::endl;

	//cv::namedWindow("Pixelation", cv::WINDOW_NORMAL);
	//cv::resizeWindow("Pixelation", 800, 600);
	cv::namedWindow("Pixelation", cv::WINDOW_FREERATIO);

	std::thread worker1 = std::thread(pixelateWithAnimation, std::ref(image), blockSize, numThreads);

	while (flag1) {
		if (flag2) {
			flag2 = false;
			std::this_thread::sleep_for(std::chrono::milliseconds(delayms));
		}
		cv::imshow("Pixelation", image);
		cv::waitKey(1);
	}

	cv::imwrite("result.jpg", image);
	cv::imshow("Pixelation", image);
	cv::waitKey(0);

	return 0;
}