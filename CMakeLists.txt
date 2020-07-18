cmake_minimum_required(VERSION 3.15)

project(FatigueDetectionSystem)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include
)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*/*.cpp")

set(EXE_NAME FatigueDetectionSystem)

message(${SOURCES})

add_executable(${EXE_NAME} ${SOURCES} src/main.cpp)

target_link_libraries(${EXE_NAME} ${OpenCV_LIBS})