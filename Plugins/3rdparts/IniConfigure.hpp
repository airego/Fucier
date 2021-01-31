//
// Created by xiaoyong on 2020/12/27.
//

#ifndef SLC_INICONFIGURE_H
#define SLC_INICONFIGURE_H

#include <log/Logger.hpp>
#include <map>

namespace slc {
    class IniConfiguration{
    private:
        Logger logger;

        bool isSpace(char c);
        bool isCommentChar(char c);
        void trim(std::string &str);
        bool analyseLine(const std::string &line, std::string &section, std::string &key, std::string &value);
        std::map<std::string, std::map<std::string, std::string> > settings_;
    public:
        void setLogger(Logger &logger);
        bool loadFile(EString file);
        bool readConfig(const std::string &filename);
        std::string readString(const char *section, const char *item, const char *default_value = "");
        int readInt(const char *section, const char *item, const int &default_value = 0);
        float readFloat(const char *section, const char *item, const float &default_value = 0.0);

        IniConfiguration();
        ~IniConfiguration();
    };
}
#endif //SLC_INICONFIGURE_H
