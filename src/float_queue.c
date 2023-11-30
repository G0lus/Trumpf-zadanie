#include <stdbool.h>
#include <float.h>

#include "float_queue.h"
#include "logger.h"

#define STATUS_ERROR -1
#define STATUS_OK 0


// queue_handle queue_init(size_t size, float* array){
queue_handle queue_init(void){
    queue_handle handle = {
        .size = MOVING_WINDOW_SIZE,
        .rear = 0,
        .front = 0,
        .length = 0,
        // .data = array
    };
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
    size_t pos = 0;
    for(size_t i = 0; i < handle->length; i++){
        pos = (handle->front + i) % handle->size;
        max = handle->data[pos] > max ? handle->data[pos] : max;
    }
    #ifdef QUEUE_LOG   
    logger("queue_max %.2f\n", max);
    #endif
    return max;
}

float queue_get_min(queue_handle* handle){
    float min = FLT_MAX;
    size_t pos = 0;
    for(size_t i = 0; i < handle->length; i++){
        pos = (handle->front + i) % handle->size;
        min = handle->data[pos] < min ? handle->data[pos] : min;
    }
    #ifdef QUEUE_LOG   
    logger("queue_min %.2f\n", min);
    #endif
    return min;
}

size_t queue_get_len(const queue_handle* handle){
    #ifdef QUEUE_LOG   
    logger("queue_len %ld\n", handle->length);
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