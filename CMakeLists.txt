cmake_minimum_required(VERSION 3.5)

project(01.ip_filter)

add_executable(ip_filter ip-filter.cpp)
set_target_properties(ip_filter PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

