//
// Created by xiaoyong on 2021/1/27.
//
#include "SuperR.h"
int main(int argc, char** argvs){

    if(argc <= 2)
    return -1;
    Logger log;
    log.Info("Start process.");

    SuperR v2m;
    v2m.params.file = argvs[1];
    v2m.params.folder = argvs[2];
    v2m.run();
    log.Info("Stop process.");
    return 0;
}