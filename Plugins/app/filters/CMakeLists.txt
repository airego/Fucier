project ("Kuafoo_App_Plugins")

SET(OpenCV_DIR ${OpenCV_DIR_Env})
FIND_PACKAGE(OpenCV REQUIRED)
add_executable(filters Filters.cpp Filters.h main.cpp)
target_link_libraries(filters ${OpenCV_LIBS} core)