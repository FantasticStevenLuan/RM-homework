#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <assert.h>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;
Mat UnionHsv(Mat mata, Mat matb, Mat ones_mat){
    Mat hsv_result=255*(ones_mat-(ones_mat-mata/255).mul(ones_mat-matb/255));
    return hsv_result;
}

int main(int argc, char ** argv) {
    vector<Mat> hsvSplit;
    Mat src=imread("/root/Documents/vision/ex2/apple.jpg");
    Mat imgHSV;
    cvtColor(src,imgHSV,COLOR_BGR2HSV);
    //因为我们读取的是彩色图，直方图均衡化需要在HSV空间做

    split(imgHSV, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    merge(hsvSplit, imgHSV);
    //extract
    Mat hsv_part1,hsv_part2;
    inRange(imgHSV,Scalar(0,140,0),Scalar(19,255,255),hsv_part1);
    inRange(imgHSV,Scalar(140,90,0),Scalar(179,255,255),hsv_part2);
    //merge
    Mat ones_mat=Mat::ones(Size(src.cols,src.rows),CV_8UC1);
    Mat hsv_extracted; hsv_extracted=UnionHsv(hsv_part1,hsv_part2,ones_mat);

    //开操作 (去除一些噪点)
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(hsv_extracted, hsv_extracted, MORPH_OPEN, element);

    //闭操作 (连接一些连通域)
    Mat hsv_result;
    morphologyEx(hsv_extracted, hsv_result, MORPH_CLOSE, element);

    namedWindow("extract result");
    imshow("extract result",hsv_extracted);

    vector< vector<cv::Point> > contour;
    vector< Vec4i > hierachy;
    findContours( hsv_result, contour, hierachy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    Mat drawer = Mat::zeros(cv::Size(src.cols, src.rows), CV_8UC3);
    Scalar LINE_COLOR= (110,0,255);
    double maxContourArea=0;
    int maxContourNum;
    for (int i=0;i<contour.size();i++) {
        if (maxContourArea<contourArea(contour[i])){
            maxContourArea=contourArea(contour[i]);
            maxContourNum=i;
        }
    }
    cout<<maxContourArea;
    vector<std::vector<cv::Point> >hull(contour.size());
    convexHull(contour[maxContourNum],hull[0]);
    drawContours(src,hull,0,LINE_COLOR,4);
    Rect rect = boundingRect(contour[maxContourNum]);
    //rectangle(src,rect, LINE_COLOR, 4);
    namedWindow("result");
    imshow("result",src);
    waitKey(0);
    return 0;
}
