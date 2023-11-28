#ifndef FLOAT_QUEUE_H
#define FLOAT_QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

struct queue_handle{
    size_t size;
    size_t rear; 
    size_t front;
    float* data;
};

typedef struct queue_handle queue_handle;

queue_handle queue_init(size_t size, float* array);
bool queue_is_empty(queue_handle* handle);
int queue_insert(queue_handle* handle, float data);
int queue_remove(queue_handle* handle, float* data);

#endif