cmake_minimum_required(VERSION 3.9)
project(kjudge_core VERSION 0.1.0 DESCRIPTION "Testing core of kjudge testing system")

set(CMAKE_CXX_STANDARD 17)

# Включение экспорта всех символов для создания динамической библиотеки
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

set(CORE_SOURCE_FILES src/unix/ktest_unix.cpp src/unix/unix_ops.cpp src/unix/unix_ops.h src/sysconf.h src/ktest.h)
set(JNI_SOURCE_FILES src/jni/jni_impl.cpp src/jni/ru_kjudge_core_SolutionLauncher.h src/jni/utils.cpp src/jni/utils.h)

add_library(kjudge_core SHARED ${CORE_SOURCE_FILES})
add_library(kjudge_core_jni SHARED ${CORE_SOURCE_FILES} ${JNI_SOURCE_FILES})
set_target_properties(kjudge_core PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER src/ktest.h)
set_target_properties(kjudge_core_jni PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER src/jni/ru_kjudge_core_SolutionLauncher.h)
