cmake_minimum_required(VERSION 3.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SRC_LIST main.cpp GameWidget.cpp widget.cpp)

find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(Qt5Core)
find_package(Qt5Gui)

qt5_wrap_cpp(MOC_SRC widget.h GameWidget.h)

add_executable(2048 ${SRC_LIST} ${MOC_SRC})

target_link_libraries(2048 Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::Gui)
