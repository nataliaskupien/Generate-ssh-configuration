cmake_minimum_required(VERSION 3.1)
project(generate_ssh_config VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(json)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

include_directories( 
    "${PROJECT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
#install(FILES ${PROJECT_SOURCE_DIR}/build/config.txt DESTINATION /home/natalia/config/)
add_subdirectory(Tests)