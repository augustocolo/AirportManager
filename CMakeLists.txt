cmake_minimum_required(VERSION 3.8)
project(AirportManager)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
set(SOURCE_FILES LIMFtraffic.dat)
set(SOURCE_FILES PlaneDB.dat)
set(SOURCE_FILES LIMFairport.dat)
add_executable(AirportManager ${SOURCE_FILES})
