cmake_minimum_required(VERSION 3.6)

# Project Information
PROJECT(bsm_test)

# CMake C++
#set(CMAKE_CXX_STANDARD 11)

# Compiler
set(CMAKE_C_COMPILER "gcc")

# Link Libraries
#LINK_LIBRARIES(boost_thread boost_asio)

# Compile Options
ADD_COMPILE_OPTIONS(-g -Wall)
set(CMAKE_EXE_LINKER_FLAGS "-static")

# Global Header files, Packages
#find_package(Boost 1.60 COMPONENTS system filesystem thread REQUIRED)
include_directories($(Boost_INCLUDE_DIRS))

# Project Files
include_directories(${CMAKE_SOURCE_DIR}/inc)
file(GLOB SRC_FILES src/*.c) 
set(BINDIR ${CMAKE_SOURCE_DIR}/bin)

ADD_EXECUTABLE(${PROJECT_NAME} main.c ${SRC_FILES})

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${BINDIR})
