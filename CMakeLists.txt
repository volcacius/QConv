cmake_minimum_required(VERSION 3.6)
project(QConv)

#Set C language requirements
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

#Set build type
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_VERBOSE_MAKEFILE ON)

#OpenMP
SET(ENABLE_OPENMP OFF)

if(ENABLE_OPENMP)
    FIND_PACKAGE(OpenMP)
endif()
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

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