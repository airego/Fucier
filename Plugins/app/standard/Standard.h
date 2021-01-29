//
// Created by xiaoyong on 2021/1/27.
//

#ifndef KUAFOO_VIDEO2MAT_H
#define KUAFOO_VIDEO2MAT_H

#include <opencv2/opencv.hpp>
#include "Logger.h"
#include "Utils.h"
#include <vector>

using namespace std;
using namespace cv;

class Standard {
private:
    Utils* util;
    vector<Mat> list;
    void Thenengrad(Mat &mat);
    void Eav(Mat &mat);
    void Energy_gradient(Mat &mat);
    void Brenner(Mat &mat);
    void SNR(Mat &mat);
    void PSNR(Mat &I1, Mat &I2);
    void SSIM(Mat &I1, Mat &I2);
    void runAction(int i);
public:
    Standard(){};
    ~Standard(){};
    struct Params{
        string  file,folder;
        int action;
        Logger* logger;
    }params;
    void run();
};


#endif //KUAFOO_VIDEO2MAT_H
