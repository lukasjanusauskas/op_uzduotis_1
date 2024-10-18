cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

project(studentai VERSION 0.1)

add_executable(main "src/main.cpp")
target_include_directories(
    main
    PRIVATE
        headers/
)