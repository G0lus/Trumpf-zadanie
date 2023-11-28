#include <stdbool.h>

#include "float_queue.h"
#include "logger.h"

#define STATUS_ERROR -1
#define STATUS_OK 0


queue_handle queue_init(size_t size, float* array){
    queue_handle handle = {
        .size = size,
        .rear = -1,
        .front = -1,
        .data = array
    };
    logger("queue init with size %ld. Array ptr %p\n", size, array);
    return handle;
}

bool queue_is_empty(queue_handle* handle){
    if(handle->front == -1 && handle->rear == -1){
        return true;
    }
    return false;
}

int queue_insert(queue_handle* handle, float data){
    if(!handle){
        return STATUS_ERROR;
    }

    if(handle->rear + 1 == handle->front || handle->rear - handle->front == handle->size){
        /* Overflow */
        return STATUS_ERROR;
    }
    if(queue_is_empty(handle)){
        logger("queue empty \n");
        handle->front = 0;
        handle->rear = 0;
    }

    handle->data[handle->rear] = data;
    logger("queue insert to rear %ld | data -> %.2f\n", handle->rear, handle->data[handle->rear]);
    handle->rear = (handle->rear + 1) % handle->size;

    return STATUS_OK;
}

int queue_remove(queue_handle* handle, float* data){
    if(!handle || !data){
        return STATUS_ERROR;
    }
    
    if(handle->front == -1){
        logger("queue underfow\n");
        return STATUS_ERROR;
    }

    *data = handle->data[handle->front];
    logger("queue remove from front %ld | data -> %.2f\n", handle->front, handle->data[handle->front]);

    if(handle->front + 1 == handle->rear){
        handle->front = -1;
        handle->rear = -1;
    }else{
        handle->front = (handle->front + 1) % handle->size;
    }
        
    return STATUS_OK;
}