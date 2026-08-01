cmake_minimum_required(VERSION 3.10.0)
project(infinity-world-builder VERSION 0.1.0 LANGUAGES C CXX)

add_executable(infinity-world-builder)

target_sources(infinity-world-builder PRIVATE 
    src/main.cpp 
    src/backend/dbio/dbio.cpp
    src/module/module.cpp
)

target_include_directories(infinity-world-builder PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/res/spdlog/include
)




