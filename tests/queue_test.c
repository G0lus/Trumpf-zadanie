#include <stdlib.h>
#include <assert.h>

#include "float_queue.h"

float data[10];

void test_insert(void){
    /* Suppressing compilator warnings */
    __attribute_maybe_unused__ queue_handle handle = queue_init();
    assert(!queue_insert(&handle, 2.0));
}

void test_remove(void){
    /* Suppressing compilator warnings */
    __attribute_maybe_unused__ queue_handle handle = queue_init();
    assert(!queue_insert(&handle, 2.0));
    assert(!queue_remove(&handle, NULL));
}

void test_get_len(void){
    /* Suppressing compilator warnings */
    __attribute_maybe_unused__ queue_handle handle = queue_init();
    assert(!queue_insert(&handle, 2.0));
    assert(queue_get_len(&handle) == 1);
}

void test_empty(void){
    /* Suppressing compilator warnings */
    __attribute_maybe_unused__ queue_handle handle = queue_init();
    assert(!queue_insert(&handle, 2.0));
    assert(!queue_remove(&handle, NULL));
    assert(queue_is_empty(&handle));
}

int main(void){
    test_empty();
    test_insert();
    return EXIT_SUCCESS;
}