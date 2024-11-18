
##
# Assignment 3
Applications both use opencv and take input "image_path, square_size, mode". 

They identify thread count depending on maximum possible threads in hardware or given "mode" being "S" (single thread). 

Then they start by counting amount of blocks with "square_size" that can be in row (+1 if some pixels left). Then how many rows of blocks will be given for each thread (same +1) and then multiply result with "square_size" to determine amount of pixels in row per thread (usualy last thread will have less in order to not go beyond maximum pixels of row of image). 

Threads will start as well as main loop that will show progress every 1ms + "delay" (further about in instructions). Threads every iteration will try to determine mean of square size (or less if it goes beyond given teritory) block (from left to right, up to down) and change entire block to it. They cant start next iteration untill all threads made to that iteration and main loop unlocks next iteration.
##
# Instructions
### Pixelization on c++ (x64)
To run this application you either need to install opencv (from offical "get started" page of opencv) or unzip files from "redist.zip" to same directory as app.
To use this application you need type this command (while being in same directory as exe):
```plaintext
pixelation1.exe <image_path> <square_size> <mode> <delay(optional)> <debug(optional)>
```
Where additionaly "delay" is for time between images (in milli seconds, 30 by default), "debug" is for console progress viewing (1 or 0, zero by default). Debug helped to identify that threads responsible for last row of image can end their work sooner due to image not being perfect for all square types.
##
### Pixelization on python (platform independent)
To run this app you need to first install requirments by this command (install pip and python first if you dont have):
```plaintext
pip install -r requirements.txt
```
```plaintext
py pixelization1.py <image_path> <square_size> <mode>
```
##