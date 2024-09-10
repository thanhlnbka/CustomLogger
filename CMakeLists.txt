cmake_minimum_required(VERSION 3.10)
project(logger_test)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the Quill package
find_package(quill REQUIRED)

# Include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(/usr/local/include)

# # Add the executable with the source files
add_executable(logger_test 
    main.cpp 
    ${CMAKE_SOURCE_DIR}/src/process1.cpp
    ${CMAKE_SOURCE_DIR}/src/process2.cpp
    ${CMAKE_SOURCE_DIR}/src/Logging.cpp
)

# Link the Quill library
target_link_libraries(logger_test PRIVATE quill::quill)
