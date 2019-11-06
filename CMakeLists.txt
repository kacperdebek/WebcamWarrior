cmake_minimum_required(VERSION 2.8)
project( Strzelnica )
set("OpenCV_DIR" "C:/Users/Michal/Documents/Libraries/opencv/build")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set("SFML_DIR" "C:/Users/Michal/Documents/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED system window graphics audio)
add_executable(Strzelnica
WebcamControl.cpp
WebcamControl.hpp
SpawnTrack.cpp
SpawnTrack.h
SpawnSocket.cpp
SpawnSocket.h
GameWindow.cpp
Menu.cpp
Menu.hpp
Monster.h
Monster.cpp)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(Strzelnica PRIVATE sfml-window sfml-graphics sfml-system sfml-audio ${OpenCV_LIBS})