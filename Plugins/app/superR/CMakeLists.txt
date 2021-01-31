project ("Kuafoo_App_Plugins")

SET(OpenCV_DIR ${OpenCV_DIR_Env})
FIND_PACKAGE(OpenCV REQUIRED)
add_executable(superr2 SuperR.cpp SuperR.h main.cpp)
target_link_libraries(superr2 ${OpenCV_LIBS} core)
