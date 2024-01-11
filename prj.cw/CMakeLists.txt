cmake_minimum_required(VERSION 3.25)
project(prj_cw)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(nifti_lib)
add_executable(main main.cpp)
find_package(OpenCV REQUIRED)
target_link_libraries(main ${OpenCV_LIBS})