cmake_minimum_required(VERSION 3.12.0)
project(Robot_Controller)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# debug setting
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

# add definition
add_compile_options(-std=c++11)
add_definitions(-D_OS_UNIX)

find_package (Eigen3 REQUIRED)

include_directories(${LIBXML2_INCLUDE_DIR})
include_directories ( "${EIGEN3_INCLUDE_DIR}" )


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/hardware_interface/  
)

# /* -------------------------------------------------------------------------- */
# /*                         Robot-Specific Dependencies                        */
# /* -------------------------------------------------------------------------- */

file(GLOB POS_CONTROL_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_interface/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/position_controller.cpp
    )

add_executable(PositinerController ${POS_CONTROL_SRC})

target_link_libraries(PositinerController PRIVATE
    pthread
    rt
    m
    )

target_link_libraries(PositinerController PRIVATE ${LIBXML2_LIBRARIES})