cmake_minimum_required(VERSION 3.26)
project(beroepsproduct)

set(CMAKE_CXX_STANDARD 23)

add_executable(beroepsproduct main.cpp
  Input.h
  Input.cpp
  Machine.h
  Machine.cpp
  Job.cpp
  Job.h
  Task.cpp
  Task.h
  Scheduler.cpp
  Scheduler.h
  Output.cpp
  Output.hpp
)
