cmake_minimum_required(VERSION 2.8)

##project(tako)

#set( CMAKE_CXX_COMPILE "g++")
set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -o3")

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/tools/tako/cmake_modules)
#set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

## dependencies

# OpenCV
#find_package(OpenCV 3.4 REQUIRED)

#RTABMap
#find_package(RTABMap REQUIRED)

#PCL
#find_package(PCL 1.7 REQUIRED)

# DBoW3
find_package(DBoW3 REQUIRED)
set( DBoW3_INCLUDE_DIRS "/usr/local/include")
set( DBoW3_LIBS "/usr/local/lib/libDBoW3.so")

## include 
set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/corelib/include
    ${PROJECT_SOURCE_DIR}/utilite/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${PCL_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/tools/tako/include
    ${DBoW3_INCLUDE_DIRS}
    )#${DBoW3_INCLUDE_DIRS}
INCLUDE_DIRECTORIES( ${INCLUDE_DIRS})
# libraries


set(LIBRARIES_TAKO
    ${OpenCV_LIBS}
    ${PCL_LIBRARIES}
    ${DBoW3_LIBS}
    )
add_definitions(${PCL_DEFINITIONS})

add_subdirectory(src)
add_subdirectory(test)
