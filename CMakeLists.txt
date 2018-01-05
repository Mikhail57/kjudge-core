cmake_minimum_required(VERSION 3.9)
project(kjudge_core VERSION 0.1.0 DESCRIPTION "Testing core of kjudge testing system")

set(CMAKE_CXX_STANDARD 17)

# Включение экспорта всех символов для создания динамической библиотеки
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#file(GLOB SOURCES src/*.cpp)
#file(GLOB SOURCES src/*.h)

set(SOURCE_LIB example.cpp)
add_library(
        kjudge_core SHARED src/unix/ktest_unix.cpp
)
set_target_properties(kjudge_core PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER src/ktest.h)
#add_executable(kjudge_core main.cpp)