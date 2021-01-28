//
// Created by xiaoyong on 2021/1/27.
//

#ifndef KUAFOO_LOGGER_H
#define KUAFOO_LOGGER_H
#include <iostream>
using namespace std;

class Logger {
public:
    Logger();
    ~Logger();
    void Info(string info);
    void Process(int val);
    void Result(string info);
};


#endif //KUAFOO_LOGGER_H
