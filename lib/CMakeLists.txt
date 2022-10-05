cmake_minimum_required(VERSION 3.5)

project(QtSTM_Interfase_LIB VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core SerialPort REQUIRED)

file(GLOB SOURCE_FILES
    #src/controllers/*.cpp
    #src/models/*.cpp
    src/core/*.cpp
    src/*.cpp)

file(GLOB HEADER_FILES
    #public/controllers/*.hpp
    #public/models/*.hpp
    public/core/*.hpp
    public/*.hpp)

add_library(${PROJECT_NAME} SHARED
  ${SOURCE_FILES}
  ${HEADER_FILES}
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    public
    #public/controllers
    #public/models
    public/core
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::SerialPort)
