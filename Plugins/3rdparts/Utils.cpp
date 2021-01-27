//
// Created by xiaoyong on 2021/1/27.
//

#include "Utils.h"

int Utils::mkdirs(string path) {

    if (!(path[path.length() - 1] == '\\' || path[path.length() - 1] == '/'))
        path.append("\\");

    int len = path.length();
    char tmpDirPath[1024] = { 0 };
    for (int i = 0; i < len; i++)
    {
        tmpDirPath[i] = path[i];
        if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
        {
            if (_access(tmpDirPath, 0) == -1)
            {
                int ret = _mkdir(tmpDirPath);
                if (ret == -1) return ret;
            }
        }
    }
    return 0;
}