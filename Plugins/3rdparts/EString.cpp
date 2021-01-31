#include <core/EString.hpp>
#include <stdio.h>
#include <stdarg.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>

namespace slc {
    EString EString::empty() {
        EString res;
        res.entity = "";
        return res;
    }

    std::string EString::getData() { return this->entity; }

    void EString::print() {
        std::cout << this->toStdString() << std::endl;
    }

    EString EString::fromChars(const char *val) {
        return EString(val);
    }

    EString EString::fromInt(int val) { return EString(val); }

    EString EString::fromDouble(double val) { return EString(val); }

    EString EString::fromStdString(const std::string val) { return EString(val); }

    EString EString::format(const char *format, ...) {
        va_list args;
        int len;
        char *buffer;

        va_start(args, format);
        len = _vscprintf(format, args) + 1;
        buffer = (char *) malloc(len * sizeof(char));
        std::vsprintf(buffer, format, args);
        EString res = EString(buffer);
        free(buffer);
        return res;
    }

#pragma region basic

    EString::~EString() {
    }

    EString::EString() {
    }

    EString EString::clone() {
        return EString(this->entity);
    }

    EString EString::concat(EString str1, EString str2) {
        auto res = str1.getData() + str2.getData();
        return EString(res);
    }

    EString EString::concat(EString str1, const char *str2) {
        auto res = str1.getData() + str2;
        return EString(res);
    }

    EString EString::concat(EString str1, const int val) {
        auto res = str1.getData() + std::to_string(val);
        return EString(res);
    }

    EString EString::concat(EString str1, const double val) {
        auto res = str1.getData() + std::to_string(val);
        return EString(res);
    }

    EString EString::concatWith(EString val) {
        return EString(this->entity + val.getData());
    }

    EString EString::concatWith(const int val) {
        return concatWith(EString::fromInt(val));
    }

    EString EString::concatWith(const double val) {
        return concatWith(EString::fromDouble(val));
    }

    EString EString::concatWith(const char *val) {
        return concatWith(EString::fromChars(val));
    }

    EString EString::concatWith(const std::string val) {
        return concatWith(EString::fromStdString(val));
    }

    std::vector<EString> split(EString& strVal, const char* val) {
        char *p;
        char va[] = "";
        p = strtok(va, val);
        std::vector<EString> res;
        while(p)
        {
            printf("%s\n", p);
            p = strtok(NULL, val);
        }

        return res;
    }

    /*
     *
     static EString Utf82Unicode(EString val);
        static EString WideByte2Acsi(EString val);
        static EString UTF_82ASCII(EString val);
        static EString Acsi2WideByte(EString val);
        static EString Unicode2Utf8(EString val);
        static EString ASCII2UTF8(EString val);
     * */
//    EString EString::Utf82Unicode(EString){
//
//    }
//    EString EString::WideByte2Acsi(EString){}
//    EString EString::UTF_82ASCII(EString){}
//    EString EString::Acsi2WideByte(EString){}
//    EString EString::Unicode2Utf8(EString){}
//    EString EString::ASCII2UTF8(EString){}

#pragma endregion

//字符串操作
#pragma region string
    EString EString::operator+(const std::string val) {
        std::string buf = this->entity + val;
        return EString(buf);
    }

    EString::EString(std::string val) {
        this->entity = val;
    }

    std::string EString::toStdString() {
        return this->entity;
    }

    const char *EString::toStdChars() {
        return this->entity.c_str();
    }
    int EString::lastIndexOf(char pattern) {
        return this->entity.find_last_of(pattern);
    }
    EString EString::substr(int start = 0, int stop = -1) {
        return EString(this->entity.substr(start,stop));
    }


#pragma endregion

#pragma region number

    EString EString::operator+(int val) {
        std::string buf;
        return EString(buf);
    }

    EString::EString(int val) {
        this->entity = std::to_string(val);
    }

    int EString::toInt32() {
        return std::atoi(this->entity.c_str());
    }

    EString EString::operator+(double val) {
        std::string buf;
        return EString(buf);
    }

    EString::EString(double val) {
        this->entity = std::to_string(val);
    }

    double EString::toDouble() {
        return std::atof(this->entity.c_str());
    }

    bool EString::isEmpty() {
        return this->entity.length() <= 0;
    }

    EString EString::toLower() {
        std::string res = this->entity;
        for (int i = 0; i < res.size(); i++)
            if(res[i] >= 'A' && res[i] <= 'Z')
                res[i] = res[i] + ('a' - 'A');
        return EString(res);
    }
    EString EString::toUpper() {
        std::string res = this->entity;
        for (int i = 0; i < res.size(); i++)
            if(res[i] >= 'a' && res[i] <= 'z')
                res[i] = res[i] - ('a' - 'A');
        return EString(res);
    }
    bool EString::equals(EString val) {
        return this->entity.compare(val.getData()) == 0;
    }
    bool EString::equals(std::string val) {
        return this->entity.compare(val) == 0;
    }

#pragma endregion

#pragma region logic

    bool EString::toBoolean() {
        return this->toLower().equals(EString::format("true"));
    }

#pragma endregion

#pragma region chars

    EString::EString(char *val) {
        this->entity = val;
    }
    EString EString::toMd5(EString val){
        if(val.equals(EString::format("utf8"))){
            return EString::format("");
        }
        return EString::format("");
    }

#pragma endregion

} // namespace slc