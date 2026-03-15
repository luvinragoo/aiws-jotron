cmake_minimum_required(VERSION 3.16)
project(aiws VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Werror)

add_executable(aiws
    src/main.cpp
    src/RectangleZone.cpp
    src/CircleZone.cpp
    src/ZoneMap.cpp
)
