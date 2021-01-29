//
// Created by xiaoyong on 2021/1/27.
//

#ifndef KUAFOO_VIDEO2MAT_H
#define KUAFOO_VIDEO2MAT_H

#include <opencv2/opencv.hpp>
#include "Logger.h"
#include "Utils.h"

using namespace std;
using namespace cv;

class SuperR {
private:
    Utils* util;
public:
    SuperR(){};
    ~SuperR(){};
    struct Params{
        string  file,folder,ext = "png";
        int start = 1,stop = -1,skip = 0;
        Logger* logger;
    }params;
    void run();
};


#endif //KUAFOO_VIDEO2MAT_H
