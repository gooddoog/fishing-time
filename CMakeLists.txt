cmake_minimum_required(VERSION 3.12)
project(fishing-time)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0043 NEW)
cmake_policy(SET CMP0071 NEW)
if(${CMAKE_VERSION} VERSION_GREATER "3.13.0")
    cmake_policy(SET CMP0079 NEW)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets Test)

include_directories(include)

include("${PROJECT_SOURCE_DIR}/cmake/config.cmake")

add_subdirectory(src)
add_subdirectory(app)
