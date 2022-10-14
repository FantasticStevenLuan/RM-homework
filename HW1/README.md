# HW1 2020.10.14
## Steven Luan
# ex1
learnt from He Zhewen.
## How to use
chmod +x ./ex1.sh
./ex1.sh + path of the file
## Idea
1. Use find and grep to look for .c/.h files that contain "hello"
- find command can search for all the files in the current folder and its subfolders
2. Use $1 to receive the perimeter the user gives, in order to search in the given folder
3. use for loop to count the total number of files
4. use data to calculate the total time used

# ex2
## Idea
1. Histogram Equalization
2. extract certain HSV ranges
3. binarization
4. do open operation to remove disturbance
5. do close operation to connect the upper part and the lower part of the apple together, since they are different in color
6. draw the outline
## Interesting feature
- used the trackbar to determine the HSV range dynamically
- I respectively extracted the upper & lower part of the apple.

# ex3
## Idea
1. graying
2. binarize
3. get outline
4. check the contours
## contour standard
1. first remove small disturbance using area: the area must be larger than a relatively small limit
2. get the bounding rectangle that has the smallest area, and check the length of the long edge
3. get the ratio of the contour area against the rectangle area
- standard 2 is to select the flying bullets
- standard 3 is to select the bouncing bullets
- so fitting either standard will be recognized as a bullet
4. if there are more than one "bullet" in one frame, select the one that has the longest circumference, since the flying ones have a longer tail
## numbering standard
- record the center of the bullet, and compare it with that of the bullet in the next frame
- if the distance between centers are smaller than a preset limit, we see them as the same one
- otherwise, we see the bullet in the next frame a new one.

# ex3-LK
This is only for testing, the perimeters weren't carefully adjusted, so it seems messy.
## Idea
1. detect the "corners" in the first frame by using goodFeaturesToTrack()
2. use calcOpticalFlowPyrLK() frame by frame to detect the motion of the objects
## What I learnt
- the basic idea of Lucas–Kanade method
- functions to achieve the method in opencv.
- in this scenario, the flying bullets are so fast that the effect of LK is relatively unsatisfactory. Comparatively, the motion of the bullets rolling slowly on the groud are recognized beautifully.
