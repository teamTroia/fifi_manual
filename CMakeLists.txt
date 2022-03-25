cmake_minimum_required(VERSION 3.16.3)
project(fifiSoccerTeam)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package( OpenCV REQUIRED )
include(${wxWidgets_USE_FILE})
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/)

set(SOURCES
    Modulos/Comunication.cpp
    Modulos/SerialPort.cpp
    Modulos/Socket.cpp
    interface/mainFrame.cpp
    fifiman.cpp)
add_executable(fifiSoccerTeam  ${SOURCES})

target_include_directories(fifiSoccerTeam PUBLIC
    "${PROJECT_SOURCE_DIR}/"
    "${PROJECT_SOURCE_DIR}/Modulos/include/"
    "${PROJECT_SOURCE_DIR}/interface/include/")

    target_link_libraries(fifiSoccerTeam ${wxWidgets_LIBRARIES})

    target_link_libraries( fifiSoccerTeam ${OpenCV_LIBS} )