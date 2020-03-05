
cmake_minimum_required(VERSION 3.5)

project(PeopleCounter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp" "${PROJECT_SOURCE_DIR}/*.h")

add_executable(PeopleCounter ${SOURCES})

target_link_libraries( PeopleCounter ${OpenCV_LIBS})
