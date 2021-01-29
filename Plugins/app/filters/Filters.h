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

class Filters {
private:
    Utils* util;
    vector<Mat> list;
    Mat guidedFilter(cv::Mat I, cv::Mat P, int type, int radius, double eps);
public:
    Filters(){};
    ~Filters(){};
    struct Params{
        string  src,folder;
        int type = 0, action = 0, file = 0;
        Logger* logger;
    }params;
    void run();
    Mat guidedFilterAction(cv::Mat guidedImg, cv::Mat inputImg, int radius, double eps);
};


#endif //KUAFOO_VIDEO2MAT_H
