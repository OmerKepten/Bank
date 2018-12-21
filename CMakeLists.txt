cmake_minimum_required(VERSION 3.12)
project(wet02)

set(CMAKE_CXX_STANDARD 14)

add_executable(wet02 main.cpp Account.cpp Account.h Bank.cpp Bank.h ATM.cpp ATM.h)