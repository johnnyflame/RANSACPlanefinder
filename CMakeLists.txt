cmake_minimum_required(VERSION 2.8)

include_directories(/home/cshome/s/steven/Public/Eigen/)

project(planeFinder)
add_executable(planeFinder
planeFinder.cpp
SimplePly.h
SimplePly.cpp
rply.h
rply.c
)




