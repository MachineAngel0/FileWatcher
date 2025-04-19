cmake_minimum_required(VERSION 3.30)
project(FileWatcher)

set(CMAKE_CXX_STANDARD 20)

add_executable(FileWatcher main.cpp
        FileWatcher.cpp
        FileWatcher.h
        Logger.cpp
        Logger.h)

