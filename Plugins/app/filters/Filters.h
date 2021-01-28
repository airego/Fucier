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
    void Thenengrad(Mat &mat);
    void Eav(Mat &mat);
    void Energy_gradient(Mat &mat);
    void Brenner(Mat &mat);
    void runAction(int i);
public:
    Filters(){};
    ~Filters(){};
    struct Params{
        string  src,folder;
        int type = 0, action = 0, file = 0;
        Logger* logger;
    }params;
    void run();
};


#endif //KUAFOO_VIDEO2MAT_H
