#include <stdlib.h>
#include <assert.h>

#include "float_queue.h"

float data[10];

void test_insert(queue_handle* handle){
    assert(!queue_insert(handle, 2.0));

    float data = 0;
    assert(!queue_remove(handle, &data));
    assert(data == 2.0);
    assert(queue_is_empty(handle));
}

int main(void){
    queue_handle handle = queue_init(10, &data[0]);
    assert(&handle);
    assert(queue_is_empty(&handle));

    test_insert(&handle);
    return EXIT_SUCCESS;
}