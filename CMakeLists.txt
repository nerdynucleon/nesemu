
# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(NESEmu VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files in the src/ directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(NESEmu ${SOURCES})

# Specify additional compiler options
target_compile_options(NESEmu PRIVATE -Wall -Wextra -pedantic -Wdeprecated-declarations)

# Link GLFW
find_package(glfw3 3.3 REQUIRED)

target_link_libraries(NESEmu glfw)

# Link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(NESEmu OpenGL::GL)

# Installation rules (optional)
# install(TARGETS NESEmu DESTINATION bin)

# Enable testing (optional)
# enable_testing()
