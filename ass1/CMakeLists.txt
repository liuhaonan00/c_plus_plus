cmake_minimum_required(VERSION 3.5)
project(wl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    EnglishWords.dat
    genlib.cpp
    genlib.h
    lexicon.cpp
    lexicon.h
    Makefile
    Makefile.dependencies
    strinfo.cpp
    strinfo.h
    strutils.cpp
    strutils.h
    WordLadder.cpp)

add_executable(wl ${SOURCE_FILES})