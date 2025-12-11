cmake_minimum_required(VERSION 3.25)
project(ketvirtas_praktinis)

set(CMAKE_CXX_STANDARD 20)

# MSVC: priversk naudoti UTF‑8 tiek šaltinio failams, tiek vykdymo metu
if (MSVC)
  add_compile_options(/utf-8)
endif()

add_executable(ketvirtas_praktinis main.cpp)
