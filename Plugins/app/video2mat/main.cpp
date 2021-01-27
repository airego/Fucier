//
// Created by xiaoyong on 2021/1/27.
//
#include "Video2Mat.h"
int main(int argc, char** argvs){

    if(argc <= 2)
    return -1;
    Logger log;
    log.Info("Start process.");

    Video2Mat v2m;
    v2m.params.file = argvs[1];
    v2m.params.folder = argvs[2];
    v2m.params.skip = 1;
    v2m.params.ext = "png";
    v2m.params.start = 0;
    v2m.params.stop = -1;
    v2m.params.logger = &log;
    v2m.run();
    log.Info("Stop process.");
    return 0;
}