cmake_minimum_required(VERSION 3.25)
project(prj.cw)

set(CMAKE_CXX_STANDARD 17)

add_library(nifti_lib library.h library.cpp)
target_include_directories(nifti_lib PUBLIC ".")

find_package(OpenCV REQUIRED)
target_link_libraries(nifti_lib ${OpenCV_LIBS})
