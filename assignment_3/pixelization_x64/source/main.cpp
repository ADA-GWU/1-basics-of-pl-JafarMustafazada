#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>

static bool is_debug = false;
static int threadLock = 0;
static int flag_total_workers = 1;
static int flag_total_worked = 0;

void processBlock(cv::Mat& image, int blockSize, int startRow, int endRow, int id) {
	cv::Rect wholeBlock(0, 0, image.cols, endRow); // helps to not get out of our block
	int current = 0;

	for (int y = startRow; y < endRow; y += blockSize) {
		for (int x = 0; x < image.cols; x += blockSize) {
			cv::Rect blockRect = cv::Rect(x, y, blockSize, blockSize) & wholeBlock;
			cv::Mat block = image(blockRect);
			cv::Scalar avgColor = cv::mean(block);
			block.setTo(avgColor);


			flag_total_worked |= id;
			if (is_debug) std::cout << ("\n" + std::to_string(flag_total_worked)
				+ " - " + std::to_string(flag_total_workers) 
				+ " - " + std::to_string(current));
			while (current == threadLock) std::this_thread::sleep_for(std::chrono::milliseconds(1));
			current++;
		}
	}

	// minus this thread
	flag_total_workers ^= id;
}

std::thread** pixelateWithAnimation(cv::Mat& image, int blockSize, int threadCount) {
	int blocksInRow = (image.rows + blockSize - 1) / blockSize;
	int blocksPerThread = (blocksInRow + threadCount - 1) / threadCount;
	int rowsPerThread = blocksPerThread * blockSize;

	std::thread** threads = new std::thread * [threadCount];

	for (int i = 0, id = 1; i < threadCount; i++, id <<= 1) {
		int startRow = i * rowsPerThread;
		int endRow = std::min(startRow + rowsPerThread, image.rows);
		threads[i] = new std::thread(processBlock, std::ref(image), blockSize, startRow, endRow, id);
	}

	return threads; // kinda like returning promise in javascript
}


int main(int argc, char** argv) {
	// if input less than 3 (+1 exe name) parametrs
	if (argc < 4) {
		std::cerr << "Usage: " << argv[0] << " <image_path> <square_size> <mode> <delay_inms> <is_debug>" << std::endl;
		return -1;
	}

	// some input
	int blockSize = std::stoi(argv[2]);
	int delayms = 30;
	if (argc > 4) delayms = std::stoi(argv[4]);
	if (argc > 5) is_debug = std::stoi(argv[5]);

	// image reading
	std::string stemp = argv[1];
	cv::Mat image = cv::imread(stemp);
	if (image.empty()) {
		std::cerr << "Could not open or find the image!" << std::endl;
		return -1;
	}

	// thread number handling (limit 31 threads even though my computer has only 20 with 14 cores :D)
	stemp = argv[3];
	int numThreads = std::thread::hardware_concurrency(); // can give 0
	if (!numThreads || stemp == "S") numThreads = 1;
	if (numThreads > 31) numThreads = 31;
	for (int i = 1; i < numThreads; i++) {
		flag_total_workers <<= 1;
		flag_total_workers++;
	}
	std::cout << "\nNumber of threads: " << numThreads;

	// window size handling
	//cv::namedWindow("Pixelation", cv::WINDOW_NORMAL);
	//cv::resizeWindow("Pixelation", 800, 600);
	cv::namedWindow("Pixelation", cv::WINDOW_FREERATIO);

	// starting threads
	bool work_goes = true;
	std::thread** threads = pixelateWithAnimation(image, blockSize, numThreads);
	std::thread worker1 = std::thread([=, &work_goes, &threads]() {
		for (int i = 0; i < numThreads; i++) {
			std::thread& t = *threads[i];
			t.join();
		}

		delete[] threads;
		threads = nullptr;
		work_goes = false;
		std::cout << "\ndone." << std::endl;
	});

	// main image loop
	while (work_goes) {
		if (flag_total_worked & flag_total_workers) threadLock++;
		cv::imshow("Pixelation", image);
		cv::waitKey(1);
		std::this_thread::sleep_for(std::chrono::milliseconds(delayms));
	}

	// when done, program ends when "any" key pressed
	// if your keyboard dont have "any" key, press enter
	cv::imwrite("result.jpg", image);
	cv::imshow("Pixelation", image);
	cv::waitKey(0);

	return 0;
}