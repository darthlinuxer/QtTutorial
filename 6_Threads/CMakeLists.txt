cmake_minimum_required(VERSION 3.14)

project(6_Threads LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Concurrent)

add_executable(6_Threads
  main.cpp
  someclass.h
  task.h
  counter.h
  producer.h
  consumer.h
  TestSlot.h

)
target_link_libraries(6_Threads Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Concurrent)

include(GNUInstallDirs)
install(TARGETS 6_Threads
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
