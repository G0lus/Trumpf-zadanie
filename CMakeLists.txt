cmake_minimum_required(VERSION 3.23)

project(trumpf_zadanie LANGUAGES C)
set(CMAKE_C_STANDARD_REQUIRED 99)
file(GLOB_RECURSE SRC
    "src/*.c"
)

include_directories(inc)
add_compile_options(-Wall -Werror)
add_executable(${PROJECT_NAME} ${SRC})

