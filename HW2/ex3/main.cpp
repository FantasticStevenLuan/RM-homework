#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <assert.h>
#include <Eigen/Dense>
#include <bits/stdc++.h>
using namespace std;
using namespace cv;
using namespace Eigen;
const int WIDTH=1200;
const int HEIGHT=800;
const int fps=30;
const int duration=5;
const float speed=0.5;
int main() {
    Size size=Size(WIDTH,HEIGHT);
    VideoWriter writer(R"(../atlas.mp4)", VideoWriter::fourcc('M', 'P', '4', '2'), fps, size);
    // 获取相机坐标
    double x_cam_w = 2., y_cam_w = 2., z_cam_w = 2.;
    // 陀螺仪给出的四元数，假定其表示相机坐标系到世界坐标系的旋转
    ifstream fin("../points.txt");
    float winput[10000][5];
    int pointnum;
    fin>>pointnum;
    for (int i = 1; i <= pointnum; i++) {
        for (int j = 1; j <= 4; j++) fin >> winput[i][j];
    }
    Mat dst;
    for (int i0=fps*duration-1;i0>=0;i0--) {
        dst=Mat::zeros(HEIGHT,WIDTH,CV_8UC3);
        double DegToRad=3.14159265/180;
        Eigen::Quaterniond q(cos((135 + i0 * speed)*DegToRad)/sqrt(2), sin((45 + 3*i0 * speed)*DegToRad)/sqrt(2), sin((45 + 2.5*i0 * speed)*DegToRad)/sqrt(2), -sin((135 + i0 * speed)*DegToRad)/sqrt(2));
        // imu 即陀螺仪
        Eigen::Matrix4d converter = [&q, &x_cam_w, &y_cam_w, &z_cam_w]() {
            // 相机的世界坐标
            Eigen::Vector3d cam_w = {x_cam_w, y_cam_w, z_cam_w};
            Eigen::Matrix4d converter = Eigen::Matrix4d::Zero();
            // Eigen::Quaterniond::matrix() 可以直接给出旋转矩阵
            Eigen::Matrix3d rot_c_to_w = q.matrix();
            // 填充外参的旋转部分
            converter.block(0, 0, 3, 3) = rot_c_to_w.transpose().cast<double>();
            // 填充外参的平移部分
            converter.block(0, 3, 3, 1) =
                    -rot_c_to_w.transpose().cast<double>() * cam_w;
            converter(3, 3) = 1.;
            return converter;
        }();

        for (int i = 1; i <= pointnum; i++) {
// 被观察物体的归⼀化世界坐标
            Eigen::Vector4d w4;
            w4 << winput[i][1], winput[i][2], winput[i][3], 1;
// 相机内参矩阵
            Eigen::Matrix<double, 3, 4> cam_f;
            cam_f << 400., 0., 190., 0., 0., 400., 160., 0., 0., 0., 1., 0.;
// 得到被观察物体的相机坐标
            Eigen::Vector4d c4 = converter * w4;
// 得到被观察物体的未归⼀化像素坐标
            Eigen::Vector3d u3 = cam_f * c4;
// 归⼀化像素坐标
            u3 /= u3(2, 0);
// 输出像素坐标
            circle(dst, Point2f(u3(0, 0), u3(1, 0)), 2, {255, 255, 255});
            std::cout << u3(0, 0) << ' ' << u3(1, 0) << '\n';
        }
        imshow("Dr.Fang is cute", dst);
        writer<<dst;
        //waitKey(5);
    }
    for (int i=1;i<=fps;i++){
        writer<<dst;
    }
    writer.release();
    waitKey(0);
    return 0;
}
