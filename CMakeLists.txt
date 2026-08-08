cmake_minimum_required(VERSION 3.10.0)
project(infinity-world-builder VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
add_executable(infinity-world-builder)

target_sources(infinity-world-builder PRIVATE 
    src/main.cpp 
    src/backend/dbio/dbio.cpp
    src/module/module.cpp
    src/backend/file_io/file_io.cpp
)

target_include_directories(infinity-world-builder PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/res/spdlog/include
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # using Clang
  target_compile_definitions(infinity-world-builder PRIVATE MACOS)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
endif()



