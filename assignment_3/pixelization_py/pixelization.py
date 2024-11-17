import cv2
import numpy as np
import threading
import time
import sys


work_done = 0
work_need = 0
thread_lock = 0
# to make access to image esaier for thread:
pixelized_image = np.ndarray


def processBlock(image, blockSize, startRow, endRow):
    global pixelized_image, work_done, work_need, thread_lock
    height, width, channels = image.shape
    current = 0

    for y in range(startRow, endRow, blockSize):
        for x in range(0, width, blockSize):
            square = image[y:min(y+blockSize, endRow), x:min(x+blockSize, width)]
            average_color = np.mean(square, axis=(0, 1))
            pixelized_image[y:y+blockSize, x:x+blockSize] = average_color

            if thread_lock == current: 
                work_done += 1
            while thread_lock == current:
                time.sleep(0.001)
            current += 1
    work_need -= 1


def main():
    global work_need, work_done, pixelized_image, thread_lock
    if len(sys.argv) < 4:
        print("Usage: python pixelization.py <image_path> <square_size> <mode>")
        return

    image_path = sys.argv[1]
    block_size = int(sys.argv[2])
    mode = sys.argv[3].upper()
    delay_pf = 0.001 # 1ms

    # Load the image
    image = cv2.imread(image_path)
    if image is None:
        print("Error: Could not open or find the image!")
        return

    # Determine the number of threads
    total_threads = 1 if mode == "S" else cv2.getNumberOfCPUs()
    print("total threads: ", total_threads)
    work_need = total_threads

    height, width, channels = image.shape
    pixelized_image = image.copy()

    # Split image into row ranges for each thread
    total_blocks = (height + block_size - 1) // block_size
    blocks_per_thread = (total_blocks + total_threads - 1) // total_threads
    rows_per_thread = blocks_per_thread * block_size

    threads = []
    for thread_id in range(total_threads):
        start_row = thread_id * rows_per_thread
        end_row = min(start_row + rows_per_thread, height)

        t = threading.Thread(target=processBlock, args=(image, block_size, start_row, end_row))
        threads.append(t)
        t.start()

    # Main loop
    while any(t.is_alive() for t in threads):
        cv2.imshow("Pixelation", pixelized_image)
        cv2.waitKey(1)
        time.sleep(delay_pf)
        if (work_done == work_need):
            work_done = 0
            thread_lock += 1

    # Wait for all threads to finish... for some reason
    for t in threads:
        t.join()
    print("done.")

    # Show final result and save it
    cv2.imwrite("result.jpg", pixelized_image)
    cv2.imshow("Pixelation", pixelized_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
