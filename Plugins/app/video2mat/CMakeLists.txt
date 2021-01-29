project ("Kuafoo_App_Plugins")

SET(OpenCV_DIR ${OpenCV_DIR_Env})
FIND_PACKAGE(OpenCV REQUIRED)
add_executable(video2mat Video2Mat.h Video2Mat.cpp main.cpp)
target_link_libraries(video2mat ${OpenCV_LIBS} core)
