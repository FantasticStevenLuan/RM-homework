#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <assert.h>
#include <bits/stdc++.h>
using namespace std;
using namespace cv;
const Scalar LINE_COLOR= {39,127,255};
const Scalar FONT_COLOR= {255,255,255};
const double FONT_SCALE=0.9;
const int DELAY=90;

Point2f recognize(Mat &src,Point2f prevRectCenter,int &num);
double PointDistance(Point2f p1,Point2f p2);
int main() {
    VideoCapture capture("/root/Documents/vision/ex3/bullet.mp4");
    long width = capture.get(CAP_PROP_FRAME_WIDTH);
    long height = capture.get(CAP_PROP_FRAME_HEIGHT);
    Size size=Size(width,height);
    double fps = capture.get(CAP_PROP_FPS);
    //double fps=10;
    //VideoWriter writer(R"(/root/Documents/vision/ex3_2/track_bullet_slowmotion.mp4)", VideoWriter::fourcc('M', 'P', '4', '2'), fps, size);
    VideoWriter writer(R"(/root/Documents/vision/ex3_2/track_bullet_originalspeed.mp4)", VideoWriter::fourcc('M', 'P', '4', '2'), fps, size);

    Mat frame;
    namedWindow("original",0);
    namedWindow("track bullet",0);
    Point2f pttemp; int numtemp=1;
    while (true){
        capture >> frame;
        if (frame.empty()) break;
        imshow("original", frame);
        pttemp=recognize(frame,pttemp,numtemp);
        imshow("track bullet",frame);
        writer<<frame;
        waitKey(DELAY);
    }
    writer.release();
    capture.release();
    return 0;
}
double PointDistance(Point2f p1,Point2f p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
Point2f recognize(Mat &src,Point2f prevRectCenter,int &num){
    //1. graying
    Mat gray;
    cvtColor(src,gray,COLOR_BGR2GRAY);

    //2. binarize
    Mat binary_img;
    threshold(gray, binary_img, 120, 200, cv::THRESH_BINARY);
    //src=binary_img;

    //3. get outline
    vector<vector<Point> > contour; vector<Vec4i> hierachy;
    findContours(binary_img, contour, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


    double contourMinArea=5;
    RotatedRect curRect,BestRect;
    double maxCir=0;
    for (int i = 0; i < contour.size(); i++) {
        //standard 1: area
        double ContArea=contourArea(contour[i]);
        if (ContArea < contourMinArea) continue;
        curRect = minAreaRect(Mat(contour[i]));
        Point2f rectPoints[4];
        curRect.points(rectPoints);

        bool flag1=false,flag2=false;
        //standard 2: max edge length
        double maxEdgeLength=0,maxEdgeLengthLim=40;
        //standard 3: ratio of the area
        double AreaRatioLim=0.3;
        double RectArea=1;
        for (int j = 0; j <=1; j++) {
            double distemp=PointDistance(rectPoints[j], rectPoints[(j + 1) % 4]);
            maxEdgeLength=max(maxEdgeLength,distemp);
            RectArea=RectArea*distemp;
        }
        if (maxEdgeLength>maxEdgeLengthLim) flag1=true;
        if (ContArea/RectArea<AreaRatioLim) flag2=true;
        //compare the circumference, select the max
        if (flag1 || flag2) {
            double curCir=arcLength(Mat(contour[i]),true);
            if (curCir>maxCir){
                maxCir=curCir;
                BestRect=curRect;
            }
        }
    }
    //no Rect selected
    if (maxCir==0) return prevRectCenter;
    //draw the rect
    Point2f rectPoints[4];
    BestRect.points(rectPoints);
    for (int j = 0; j < 4; j++) {
        line(src, rectPoints[j], rectPoints[(j + 1) % 4], LINE_COLOR, 1, 8, 0);
    }
    //calculate the change in the position of the center
    Point2f curRectCenter=BestRect.center;
    double centerDist= PointDistance(curRectCenter,prevRectCenter);
    double centerDistLim_l=20,centerDistLim_h=120;
    if (centerDist>centerDistLim_l && centerDist<centerDistLim_h){
        Point textPoint=Point(curRectCenter.x,curRectCenter.y);
        putText(src, to_string(num),textPoint,FONT_HERSHEY_SIMPLEX,FONT_SCALE,FONT_COLOR);
    }
    else{
        num++;
        Point textPoint=Point(curRectCenter.x,curRectCenter.y);
        putText(src, to_string(num),textPoint,FONT_HERSHEY_SIMPLEX,FONT_SCALE,FONT_COLOR);
    }
    cout<<num<<endl;
    return curRectCenter;
}
