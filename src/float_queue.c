#include <stdbool.h>

#include "float_queue.h"
#include "logger.h"

#define STATUS_ERROR -1
#define STATUS_OK 0


queue_handle queue_init(size_t size, float* array){
    queue_handle handle = {
        .size = size,
        .rear = 0,
        .front = 0,
        .length = 0,
        .data = array
    };
    #ifdef QUEUE_LOG
    logger("queue init with size %ld. Array ptr %p\n", size, array);
    #endif
    return handle;
}

bool queue_is_empty(const queue_handle* handle){
    return handle->length == 0;
}

bool queue_is_full(const queue_handle* handle){
    return handle->length == handle->size;
}

float queue_get_max(queue_handle* handle){
    float max = 0;
    for(size_t i = 0; i < handle->length; i++){
        size_t pos = (handle->front + i) % handle->size;
        max = handle->data[pos] > max ? handle->data[pos] : max;
    }
    #ifdef QUEUE_LOG   
    logger("queue_max %.2f\n", max);
    #endif
    return max;
}

size_t queue_get_len(const queue_handle* handle){
    #ifdef QUEUE_LOG   
    logger("queue_max %ld\n", handle->length);
    #endif
    return handle->length;
}

int queue_insert(queue_handle* handle, float data){
    if(!handle){
        return STATUS_ERROR;
    }

    if(queue_is_full(handle)){
        /* Overflow */
        return STATUS_ERROR;
    }
    
    handle->data[handle->rear] = data;
    #ifdef QUEUE_LOG
    logger("queue insert to rear %ld | data -> %.2f\n", handle->rear, handle->data[handle->rear]);
    #endif
    if(!queue_is_full(handle)){
        handle->rear = (handle->rear + 1) % handle->size;
    }
    handle->length++;
    return STATUS_OK;
}

int queue_remove(queue_handle* handle, float* data){
    if(!handle){
        return STATUS_ERROR;
    }
    
    if(queue_is_empty(handle)){
        #ifdef QUEUE_LOG
        logger("queue underfow\n");
        #endif
        return STATUS_ERROR;
    }

    if(data){
        *data = handle->data[handle->front];
    }

    #ifdef QUEUE_LOG
    logger("queue remove from front %ld | data -> %.2f\n", handle->front, handle->data[handle->front]);
    #endif
    if(!queue_is_empty(handle)){
        handle->front = (handle->front + 1) % handle->size;
    }
    handle->length--;
    return STATUS_OK;
}