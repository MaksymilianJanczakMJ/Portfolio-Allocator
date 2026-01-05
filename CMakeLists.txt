cmake_minimum_required(VERSION 4.0)
project(Portfolio_allocator C)

set(CMAKE_C_STANDARD 90)

add_executable(Portfolio_allocator
        main.c
        allocator.c
        allocator.h
        ui.c
        ui.h
        config.h)
