cmake_minimum_required(VERSION 3.12)

project(ECS CXX)

add_subdirectory(src)

target_compile_options(ECS PRIVATE -Wall -Wextra -Wpedantic)
