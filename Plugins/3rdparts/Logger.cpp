//
// Created by xiaoyong on 2021/1/27.
//

#include "Logger.h"

Logger::Logger() {}
Logger::~Logger() {}
void Logger::Info(string str) {
    cout<<"l:"<<str<<endl;
}
void Logger::Process(int val) {
    cout<<"p:"<<val<<endl;
}