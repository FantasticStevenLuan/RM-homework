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