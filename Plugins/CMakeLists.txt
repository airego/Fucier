# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("Kuafoo")

SET(OpenCV_DIR_Env D:/Env/opencv/mingw/)
include_directories(3rdparts)
add_subdirectory(3rdparts)
add_subdirectory(app/)