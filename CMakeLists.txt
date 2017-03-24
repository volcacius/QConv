cmake_minimum_required(VERSION 3.6)
project(QConv)

#Set C language requirements
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

#Set build type
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_VERBOSE_MAKEFILE ON)

#Add subdir for compiling the library on which the executable depends on
add_subdirectory(src)
#Add subdir for compiling the tests
add_subdirectory(test)

#Define executable src files
set(QCONV_EXE_SRC main.c)

#Define output executable
add_executable(qconv_exe ${QCONV_EXE_SRC})

#Link against the library dependencies
target_link_libraries(qconv_exe
        PUBLIC qconv_lib)