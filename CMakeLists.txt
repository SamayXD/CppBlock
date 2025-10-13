# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CppBlock VERSION 1.0)

# Use C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(blockchain ${SOURCES}
        include/Transaction.h
        include/Utils.h
)

# Optional: Add compiler warnings
if(MSVC)
    target_compile_options(blockchain PRIVATE /W4)
else()
    target_compile_options(blockchain PRIVATE -Wall -Wextra -pedantic)
endif()