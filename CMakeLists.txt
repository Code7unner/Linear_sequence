cmake_minimum_required(VERSION 3.10)
project(linear_sequence C)

set(CMAKE_C_STANDARD 99)

add_library(linear_sequence linear_sequence.c linear_sequence.h)