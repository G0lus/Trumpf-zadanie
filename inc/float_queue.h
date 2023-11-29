#ifndef FLOAT_QUEUE_H
#define FLOAT_QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

struct queue_handle{
    size_t size;
    size_t length;
    size_t rear; 
    size_t front;
    float* data;
};

typedef struct queue_handle queue_handle;

queue_handle queue_init(size_t size, float* array);
bool queue_is_empty(const queue_handle* handle);
bool queue_is_full(const queue_handle* handle);
float queue_get_max(queue_handle* handle);
int queue_insert(queue_handle* handle, float data);
int queue_remove(queue_handle* handle, float* data);
size_t queue_get_len(const queue_handle* handle);

#endif