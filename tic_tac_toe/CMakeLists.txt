cmake_minimum_required(VERSION 3.6)
project(tictactoe VERSION "0.0.0" LANGUAGES CXX)

if(NOT MSVC)
  add_definitions(-Wall)
  add_definitions(-pedantic)
endif()

add_executable(tictactoe main.cpp)
set_target_properties(tictactoe PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
