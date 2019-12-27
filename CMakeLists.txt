cmake_minimum_required(VERSION 3.7)
project(Asteroids)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11")
set(SOURCE src/)
set(INCLUDE include/)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

include_directories(
        ${SOURCE}
        ${INCLUDE})

link_directories(
        ${SOURCE}
        ${INCLUDE})

file(GLOB all
        "${INCLUDE}*.hpp"
        "${SOURCE}*.cpp")

add_executable(${PROJECT_NAME} ${all})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES}  ${SDL2_IMAGE_LIBRARIES})
