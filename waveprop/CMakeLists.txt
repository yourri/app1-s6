cmake_minimum_required(VERSION 3.1)

project(AssetConv VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(CMAKE_BUILD_TYPE            Debug) # Change to RelWithDebInfo or Release


add_executable(wave_prop src/wave_prop.cpp)
target_link_libraries(wave_prop pthread)
