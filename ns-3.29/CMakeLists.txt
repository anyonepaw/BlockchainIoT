########## GLOBAL CONFIGURATION ##########
cmake_minimum_required(VERSION 3.13)
project(PROJECT_NAME ns-3.29)

set(CMAKE_CXX_STANDARD 14)

 

#INCLUDE_DIRECTORIES(  /usr/local/include )
#LINK_DIRECTORIES(  /usr/local/lib )


file(GLOB LIBRARIES "/Users/anyonepaw/CLionProjects/BlockchainIoT/ns-3.29/build/lib")
message("LIBRARIES = ${LIBRARIES}")

LINK_LIBRARIES(ns-3.29  ${LIBRARIES})

target_link_libraries(ns-3.29 ${PROJECT_NAME}
   )

set(Sources /Users/anyonepaw/CLionProjects/BlockchainIoT/ns-3.29/src/bridge/helper/bridge-helper.cc)
set(Headers /Users/anyonepaw/CLionProjects/BlockchainIoT/ns-3.29/src/bridge/helper/bridge-helper.h)
set(Sources /Users/anyonepaw/CLionProjects/BlockchainIoT/ns-3.29/src/network/model/net-device.cc)
set(Headers /Users/anyonepaw/CLionProjects/BlockchainIoT/ns-3.29/src/bridge/helper/bridge-helper.h)
add_executable(ns3 ${Sources} ${Headers})