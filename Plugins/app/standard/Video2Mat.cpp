//
// Created by xiaoyong on 2021/1/27.
//

#include "Video2Mat.h"
void Video2Mat::run() {
    VideoCapture capture;
    if(!capture.open(this->params.file)){
        this->params.logger->Info("Cannot open the file.");
        return;
    }
    if(!capture.isOpened()){
        this->params.logger->Info("Fail to open file.");
        return;
    }

    util->mkdirs(this->params.folder);

    this->params.logger->Info("The file has opened.");
    this->params.logger->Process(0);
    Mat current;
    capture >> current;
    char path[1024];

    int count = capture.get(CAP_PROP_FRAME_COUNT);
    if(this->params.skip <= 0)
        this->params.skip = 1;

    int per = count / 100;
    per++;
    int process = 0;
    for (int i = 0; !current.empty(); ++i, capture >> current) {
        sprintf(path,"%s/%d.%s",this->params.folder.c_str(),i,this->params.ext.c_str());
        imwrite(path,current);
        if(i % per == 0)
            this->params.logger->Process(++process);
    }
    capture.release();

    this->params.logger->Info("Task finished.");
    this->params.logger->Process(100);
}