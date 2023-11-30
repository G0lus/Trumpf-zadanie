cmake_minimum_required(VERSION 3.23)

project(trumpf_zadanie LANGUAGES C)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB_RECURSE SRC
    "src/*.c"
)

include_directories(inc)
add_compile_definitions(
    # QUEUE_LOG
    MOVING_WINDOW_SIZE=3
)
add_compile_options(
    "-Wall" 
    "-Werror"
)

add_executable(${PROJECT_NAME} ${SRC})

enable_testing(true)
add_subdirectory(tests)