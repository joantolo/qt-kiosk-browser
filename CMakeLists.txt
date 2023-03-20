cmake_minimum_required(VERSION 3.5)

project(qt-kiosk-browser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS WebEngineWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS WebEngineWidgets)

add_executable(qt-kiosk-browser main.cpp)
target_link_libraries(qt-kiosk-browser PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

install(TARGETS qt-kiosk-browser RUNTIME DESTINATION bin)
