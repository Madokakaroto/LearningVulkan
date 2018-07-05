cmake_minimum_required(VERSION 3.10)


project(LearningVulkan)
set(CMAKE_CXX_STANDARD 17)
add_executable(LearningVulkan src/LowLevel/hello_vulkan.cpp)
target_link_libraries(LearningVulkan -lglfw3)