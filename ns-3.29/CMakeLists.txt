########## GLOBAL CONFIGURATION ##########
cmake_minimum_required(VERSION 3.13)
project(ns-3.29)

set(CMAKE_CXX_STANDARD 14)

 

#INCLUDE_DIRECTORIES(  /usr/local/include )
#LINK_DIRECTORIES(  /usr/local/lib )


file(GLOB LIBRARIES "/Users/anyonepaw/CLionProjects/BlockchainIoT/ns-3.29/build/lib")
message("LIBRARIES = ${LIBRARIES}")

LINK_LIBRARIES(ns-3.29  ${LIBRARIES})