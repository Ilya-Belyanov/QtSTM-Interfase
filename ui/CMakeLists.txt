cmake_minimum_required(VERSION 3.5)

project(QtSTM_Interfase VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui SerialPort REQUIRED)

file(GLOB SOURCE_FILES
    src/*.cpp
    #delegates/*.cpp
    components/*.cpp)

file(GLOB HEADER_FILES
    src/*.hpp
    #delegates/*.hpp
    components/*.hpp)

file(GLOB UI_FILES
    view/*.ui)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${UI_FILES}
    #res.qrc
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    src
    #delegates
    components
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::SerialPort
        QtSTM_Interfase_LIB)
