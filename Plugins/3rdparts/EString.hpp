#include <iostream>
#include <string>
#include <vector>
#ifndef SLC_ESTRING
#define SLC_ESTRING
class EString
{
private:
    char *p;
    std::string entity = "";
public:
    int Length = -1;

    EString(/* args */);
    ~EString();

    static EString fromInt(int val);
    static EString fromDouble(double val);
    static EString fromStdString(const std::string val);
    static EString fromChars(const char* val);
    static EString format(const char* formater, ...);
    static EString empty();

    void print();
    std::string getData();
    //字符串操作
    EString operator+(const std::string val);
    EString(std::string val);
    std::string toStdString();
    const char* toStdChars();
    EString clone();
    bool isEmpty();
    EString concat(EString str1,EString str2);
    EString concat(EString str1,const std::string str2);
    EString concat(EString str1,const char* str2);
    EString concat(EString str1,const int val);
    EString concat(EString str1,const double val);
    EString concatWith(EString val);
    EString concatWith(const std::string val);
    EString concatWith(const char* val);
    EString concatWith(const int val);
    EString concatWith(const double val);
    EString* split(const char* splitor);
    EString substr(int start, int stop);
    int lastIndexOf(char pattern);

    EString toMd5(EString encoding = EString::format("utf8"));

    EString toLower();
    EString toUpper();
    bool equals(EString val);
    bool equals(std::string val);

    //数字的操作
    EString operator+(int val);
    EString(int val);
    int toInt32();
    EString operator+(double val);
    EString(double val);
    double toDouble();

    //逻辑操作符
    bool toBoolean();

    //逻辑操作符
    EString(char* val);
};
#endif