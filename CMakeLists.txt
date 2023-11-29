cmake_minimum_required(VERSION 3.23)

project(trumpf_zadanie LANGUAGES C)
set(CMAKE_C_STANDARD_REQUIRED 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC
    "src/*.c"
)

include_directories(inc)
add_compile_definitions(
    # QUEUE_LOG
)
add_compile_options(-Wall -Werror)

add_executable(${PROJECT_NAME} ${SRC})

enable_testing(true)
add_subdirectory(tests)