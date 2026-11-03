
cmake_minimum_required(VERSION 3.21) 

project(HudsonB2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV CONFIG REQUIRED)

add_executable(replay
    docs/milestones/01-aruco-bench/src/replay.cpp
)

target_link_libraries(replay
    PRIVATE ${OpenCV_LIBS}
)
add_executable(aruco_detector
    docs/milestones/01-aruco-bench/src/aruco_detector.cpp
)

target_link_libraries(aruco_detector
    PRIVATE ${OpenCV_LIBS}
)
