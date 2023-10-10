cmake_minimum_required(VERSION 3.14)

project(CPlusPlusUniqueness LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(CPlusPlusUniqueness
  main.cpp
  animal.h animal.cpp
  dog.h dog.cpp
  zoo.h zoo.cpp
  cat.h cat.cpp
  PointersAndMemory.h PointersAndMemory.cpp
  zookeeper.h zookeeper.cpp
  animalstatus.h
  PropertiesAndEvents.cpp
  PropertiesAndEvents.h
)
target_link_libraries(CPlusPlusUniqueness Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS CPlusPlusUniqueness
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
