project ("Kuafoo_App_Video2Mat")

SET(OpenCV_DIR ${OpenCV_DIR_Env})
FIND_PACKAGE(OpenCV REQUIRED)
add_executable(standard Standard.h Standard.cpp main.cpp)
target_link_libraries(standard ${OpenCV_LIBS} core)
