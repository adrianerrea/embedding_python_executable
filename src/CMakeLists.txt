project(embeddingImpl)
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set (CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath,$ORIGIN -Wl,-rpath,$ORIGIN/my_python/lib")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../my_python/include/python3.9/)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../my_python/lib)
# Build the shared libraries
add_library(my_code my_code.cpp my_code.h structs.h stb_image.h)
add_executable(binary_exec main.cpp)
# Add the Python libraries to the target link libraries
target_link_libraries(binary_exec my_code -lpython3.9)
