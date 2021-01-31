project ("Kuafoo_App_Plugins")

SET(OpenCV_DIR ${OpenCV_DIR_Env})
FIND_PACKAGE(OpenCV REQUIRED)

add_executable(sfm SFMController.h SFMController.cpp)
target_link_libraries(sfm ${OpenCV_LIBS} core)

add_executable(superr SuperRController.h SuperRController.cpp)
target_link_libraries(superr ${OpenCV_LIBS} core)