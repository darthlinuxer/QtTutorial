cmake_minimum_required(VERSION 3.14)

project(4_QtMultiThread LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(4_QtMultiThread
  main.cpp
  mythread.h mythread.cpp
  worker.h worker.cpp
  workerwiththreadencapsulated.h workerwiththreadencapsulated.cpp
)
target_link_libraries(4_QtMultiThread Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS 4_QtMultiThread
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
