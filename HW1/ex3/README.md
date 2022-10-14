# ex3-LK
This is only for testing, the perimeters weren't carefully adjusted, so it seems messy.
## Idea
1. detect the "corners" in the first frame by using goodFeaturesToTrack()
2. use calcOpticalFlowPyrLK() frame by frame to detect the motion of the objects
## What I learnt
- the basic idea of Lucas–Kanade method
- functions to achieve the method in opencv.
- in this scenario, the flying bullets are so fast that the effect of LK is relatively unsatisfactory. Comparatively, the motion of the bullets rolling slowly on the groud are recognized beautifully.