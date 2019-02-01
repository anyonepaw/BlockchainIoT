cmake_minimum_required(VERSION 3.13)
project(BlockchainIoT C CXX)


set(CMAKE_CXX_STANDARD 14)


#Standart settings
add_executable(BlockchainIoT main.cpp) #defines our binary with all linked source files.

add_subdirectory(ns-3.29)

INCLUDE_DIRECTORIES(/ns-3.29/build/ns3)
LINK_DIRECTORIES(/ns-3.29/build/lib)

target_link_libraries(BlockchainIoT ns-3.29)

install(TARGETS BlockchainIoT DESTINATION bin) #install tells cmake to install our binary
#into the bin directory of the install directory.











#rosbuild_add_executable(kinectueye src/kinect_ueye.cpp)
#TARGET_LINK_LIBRARIES(kinectueye lib1 lib2 lib2 ...)


