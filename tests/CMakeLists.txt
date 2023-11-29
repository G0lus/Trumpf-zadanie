include_directories(${PROJECT_SOURCE_DIR}/inc)

add_compile_definitions(
    QUEUE_LOG
)
add_executable(queue_test 
    queue_test.c 
    ${PROJECT_SOURCE_DIR}/src/float_queue.c
    ${PROJECT_SOURCE_DIR}/src/logger.c
)

add_test(
    NAME "Queue testing" 
    COMMAND queue_test
)