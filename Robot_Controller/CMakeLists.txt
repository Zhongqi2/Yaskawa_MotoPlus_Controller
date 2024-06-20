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

# Define the hardware_interface library
file(GLOB HARDWARE_INTERFACE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_interface/*.cpp
)
add_library(hardware_interface ${HARDWARE_INTERFACE_SRC})

# Define the PositinerController executable
# Make sure to exclude the hardware_interface sources if they are not needed directly by the executable
add_executable(PositinerController ${CMAKE_CURRENT_SOURCE_DIR}/src/position_controller.cpp)

# Link the hardware_interface library to PositinerController
target_link_libraries(PositinerController PRIVATE hardware_interface)

# Link external libraries to PositinerController
target_link_libraries(PositinerController PRIVATE
    pthread
    rt
    m
    ${LIBXML2_LIBRARIES}
)

# Install the hardware_interface library to /usr/local/lib
install(TARGETS hardware_interface
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Install the header files to /usr/local/include/hardware_interface
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/hardware_interface/
    DESTINATION include/hardware_interface
    FILES_MATCHING PATTERN "*.h"
)