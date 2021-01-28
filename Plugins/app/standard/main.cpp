//
// Created by xiaoyong on 2021/1/27.
//
#include "Standard.h"
int main(int argc, char** argvs){

    if(argc <= 2)
    return -1;
    Logger log;
    log.Info("Start process.");

    Standard standard;
    standard.params.logger = &log;
    standard.params.file = argvs[1];
    standard.params.action = std::atoi(argvs[2]);
    standard.run();

    log.Info("Stop process.");
    return 0;
}