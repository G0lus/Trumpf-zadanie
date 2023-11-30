#include <stdlib.h>
#include <assert.h>

#include "float_queue.h"

float data[10];

void test_insert(void){
    queue_handle handle = queue_init();
    assert(!queue_insert(&handle, 2.0));
    float val = 0;
    assert(!queue_remove(&handle, &val));
}

void test_empty(void){
    queue_handle handle = queue_init();
    assert(!queue_insert(&handle, 2.0));
    assert(!queue_remove(&handle, NULL));
    assert(queue_is_empty(&handle));
}

int main(void){
    test_empty();
    test_insert();
    return EXIT_SUCCESS;
}