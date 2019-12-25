cmake_minimum_required(VERSION 3.6)
project(Asteroids)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11")
set(SOURCE src/)
set(INCLUDE include/)
set(FR_SOURCE Framework/src)
set(FR_INCLUDE Framework/inc)

include_directories(
        ${SOURCE}
        ${INCLUDE}
        ${FR_SOURCE}
        ${FR_INCLUDE})

link_directories(
        ${SOURCE}
        ${INCLUDE}
        ${FR_SOURCE}
        ${FR_INCLUDE})

file(GLOB all
        "${INCLUDE}*.hpp"
        "${SOURCE}*.cpp"
        "${FR_SOURCE}*.cpp"
        ${FR_INCLUDE}*.h)

add_executable(${PROJECT_NAME} ${all})

target_link_libraries(${PROJECT_NAME} ${MY_LIBNAME})

add_subdirectory(Framework/)