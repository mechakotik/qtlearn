cmake_minimum_required(VERSION 3.31)
project(test-platform)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Multimedia)
qt_standard_project_setup()

qt_add_executable(test-platform
        application.qrc
        src/main.cpp
)

qt_add_qml_module(test-platform
        URI path
        VERSION 1.0
        QML_FILES qml/main.qml
)

target_link_libraries(test-platform PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Multimedia
)

target_include_directories(test-platform PRIVATE src)

