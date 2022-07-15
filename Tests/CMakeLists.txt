cmake_minimum_required(VERSION 3.1)
project(tests)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB SOURCES "../src/*.cpp*")
file(GLOB HEADERS "../include/*.h")

add_executable(${PROJECT_NAME} 
arguments_test.cpp 
save_data_test.cpp
parse_file_test.cpp 
integration_tests.cpp
${SOURCES})

target_link_libraries(
  ${PROJECT_NAME}
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})