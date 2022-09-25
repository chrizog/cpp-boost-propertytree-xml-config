cmake_minimum_required(VERSION 3.0)

project(boost_property_tree)

find_package(Boost 1.76.0 REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(boost_property_tree
  main.cpp
  application_settings.cpp
  application_settings.h)

target_compile_options(boost_property_tree PUBLIC -std=c++14 -Wall -g -O0)

target_include_directories(boost_property_tree PUBLIC ${Boost_INCLUDE_DIR})

install(TARGETS boost_property_tree DESTINATION 
  bin)