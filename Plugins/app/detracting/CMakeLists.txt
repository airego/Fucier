project ("Kuafoo_App_Plugins")

SET(OpenCV_DIR ${OpenCV_DIR_Env})
FIND_PACKAGE(OpenCV REQUIRED)

add_executable(dt DTracingController.h DTracingController.cpp)
target_link_libraries(dt ${OpenCV_LIBS} core)