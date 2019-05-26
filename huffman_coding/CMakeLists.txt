cmake_minimum_required(VERSION 3.6)
project(huffman_coding VERSION "0.0.0" LANGUAGES CXX)

if(NOT MSVC)
  add_definitions(-Wall)
  add_definitions(-pedantic)
endif()

add_executable(huffman_coding main.cpp)
set_target_properties(huffman_coding PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)