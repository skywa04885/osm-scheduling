cmake_minimum_required(VERSION 3.26)
project(beroepsproduct)

set(CMAKE_CXX_STANDARD 17)

add_executable(beroepsproduct main.cpp
        Config.h
        Config.cpp
        Machine.h
        Machine.cpp
        Job.cpp
        Job.h
        Task.cpp
        Task.h
        output.cpp
        output.h
)
