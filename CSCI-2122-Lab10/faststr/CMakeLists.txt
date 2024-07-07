cmake_minimum_required(VERSION 3.18)
project(faststr C)
set_source_files_properties(strlen.c PROPERTIES COMPILE_OPTIONS "-O3;-fno-builtin")

set(CMAKE_C_STANDARD 99)

add_executable(faststr main.c
        histogram.c
        strlen.c
        ticks.c)
