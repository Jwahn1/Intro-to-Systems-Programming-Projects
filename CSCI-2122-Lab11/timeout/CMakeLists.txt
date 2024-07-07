cmake_minimum_required(VERSION 3.18)
project(timeout C)

set(CMAKE_C_STANDARD 99)

add_executable(timeout main.c)
add_executable(snooze snooze.c)
