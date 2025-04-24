cmake_minimum_required(VERSION 3.20)
project(smart_ptr)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(smart_ptr
        src/main.cpp
        src/main_window.cpp
        src/add_user_dialog.cpp
        src/add_book_dialog.cpp
        src/user_books_dialog.cpp
)

target_link_libraries(smart_ptr PRIVATE Qt6::Widgets)

set_target_properties(smart_ptr PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)
