# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Sets the project name based on the directory's name
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME ProjectName)
string(REPLACE " " "_" ProjectId ${ProjectName})
project(${ProjectName})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the C standard (C23 as you mentioned earlier)
set(CMAKE_C_STANDARD 23)

set(CMAKE_C_EXTENSIONS OFF)

# Add the executable (main source file)
add_executable(${CMAKE_PROJECT_NAME} src/main.c)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Link against the static library
target_link_libraries(${CMAKE_PROJECT_NAME} /usr/lib/libglfw.so raylib glfw m pthread dl rt)

find_package(glfw3 REQUIRED)

# Optionally, add custom compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -pedantic -Wextra -Wshadow -g -lraylib -lm -lpthread -ldl -lrt")

