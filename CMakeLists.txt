cmake_minimum_required(VERSION 3.10.0)
project(infinity-world-builder VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
add_executable(infinity-world-builder)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


target_sources(infinity-world-builder PRIVATE 
# Define the executable and its source files
    src/main.cpp 
    src/backend/dbio/dbio.cpp
    src/module/module.cpp
    src/backend/file_io/file_io.cpp
)

# Handle include directories
target_include_directories(infinity-world-builder PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/res/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/res/sqlite
)



# --- Cross-Platform OS Configuration ---
if(APPLE)
    # Target definition for macOS
    target_compile_definitions(infinity-world-builder PRIVATE MACOS)
    
elseif(WIN32)
    # Target definition for Windows
    target_compile_definitions(infinity-world-builder PRIVATE WINDOWS)
    
    # Optional: Fixes common Windows/MSVC issues like min/max macro conflicts
    target_compile_definitions(infinity-world-builder PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
endif()