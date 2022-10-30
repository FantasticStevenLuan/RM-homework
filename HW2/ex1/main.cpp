#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <assert.h>
#include <bits/stdc++.h>
using namespace std;
using namespace cv;
int main() {
    Mat src=imread("/root/Documents/vision/HW2/ex1/carplate.png");
    if (src.empty()){
        printf("can't load image...");
        return -1;
    }
    namedWindow("input image",0);
    imshow("input image",src);
    vector<Point2f> src_corners(4);
    src_corners[0]=Point2f(746,413);
    src_corners[1]=Point2f(956,415);
    src_corners[2]=Point2f(755,484);
    src_corners[3]=Point2f(964,485);
    vector<Point2f> dst_corners(4);
    dst_corners[0]=Point2f(0,0);
    dst_corners[1]=Point2f(200,0);
    dst_corners[2]=Point2f(0,150);
    dst_corners[3]=Point2f(200,150);
    Mat m= getPerspectiveTransform(src_corners,dst_corners);
    Mat resultimg;
    warpPerspective(src,resultimg,m,Size(200,150),INTER_LINEAR);
    imshow("Perspective",resultimg);
    imwrite("/root/Documents/vision/HW2/ex1/carplate_out.png",resultimg);
    waitKey(0);
    return 0;
}
