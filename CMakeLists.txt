cmake_minimum_required(VERSION 3.19.2)

project(enyin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package ( OpenGL REQUIRED )

add_subdirectory(lib/glfw-3.3.6)
add_subdirectory(lib/tinygltf)

add_executable(enyin 
  main.cpp)

target_link_libraries(enyin glfw)
target_link_libraries(enyin tinygltf)

if (APPLE)
  target_link_libraries(enyin "-framework OpenGL")
endif()

file(GLOB_RECURSE assets ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)

add_custom_command(
        TARGET enyin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/assets
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
