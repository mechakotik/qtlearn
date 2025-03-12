cmake_minimum_required(VERSION 3.31)
project(ambiance)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Multimedia)
qt_standard_project_setup()

qt_add_executable(ambiance
        application.qrc
        src/main.cpp
        src/ambiance.cpp
        src/sound.cpp
)

qt_add_qml_module(ambiance
    URI path
    VERSION 1.0
    QML_FILES qml/main.qml
)

target_link_libraries(ambiance PRIVATE Qt6::Quick Qt6::Multimedia)
target_include_directories(ambiance PRIVATE src)
