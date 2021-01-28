//
// Created by xiaoyong on 2021/1/27.
//
#include "Filters.h"
/**
 * 滤波器
 *
 * filters [file] [type] [action] [src]
 *
 * file：是类型，指定操作对象是文件或者文件夹。
 * type: 是类型，指定操作对象是图片或者是视频
 * action: 是动作，指定操作或处理算法
 * src: 是文件，指定操作的原始文件
 *
 * @param argc
 * @param argvs
 * @return
 */
int main(int argc, char** argvs){

    if(argc <= 2)
    return -1;
    Logger log;
    log.Info("Start process.");

    Filters standard;
    standard.params.logger = &log;
    standard.params.file = atoi(argvs[1]);
    standard.params.type = std::atoi(argvs[2]);
    standard.params.action = std::atoi(argvs[3]);
    standard.params.src = argvs[4];
    standard.run();

    log.Info("Stop process.");
    return 0;
}