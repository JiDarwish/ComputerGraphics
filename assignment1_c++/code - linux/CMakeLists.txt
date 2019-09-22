cmake_minimum_required(VERSION 3.5)

# Project name shown when building
set(PROJECT_NAME Assignment_1_Project)

# Create project
project(${PROJECT_NAME})

# Compiler and IDE configuration
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Create executable and link everything to it
add_executable(${PROJECT_NAME} Exercises.h Exercises.cpp)