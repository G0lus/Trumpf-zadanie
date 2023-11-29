#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "logger.h"
#include "float_queue.h"

#define ARGV_REQUIRED 2U
#define DATA_CHUNK_SIZE 8096U
#define VALUES_CHUNK_SIZE 2048U
#define MOVING_WINDOW_SIZE 3U
#define VALUES_COLUMNS 4U


void moving_max(size_t window_size, size_t n, float in[static n], float out[static n]){
    float window[window_size];
    queue_handle handle = queue_init(window_size, &window[0]);
    for(size_t i = 0; i < n; i++){
        
        if(queue_is_full(&handle)){
            queue_remove(&handle, NULL);
        }
        queue_insert(&handle, in[i]);
        out[i] = queue_get_max(&handle);
    }
}

void moving_min(size_t window_size, size_t n, float in[static n], float out[static n]){
    float window[window_size];
    queue_handle handle = queue_init(window_size, &window[0]);
    for(size_t i = 0; i < n; i++){
        
        if(queue_is_full(&handle)){
            queue_remove(&handle, NULL);
        }
        queue_insert(&handle, in[i]);
        out[i] = queue_get_min(&handle);
    }
}

void moving_average(size_t window_size, size_t n, float in[static n], float out[static n]){
    float window[window_size];
    queue_handle handle = queue_init(window_size, &window[0]);
    float sum = 0;
    
    for(size_t i = 0; i < n; i++){
        if(queue_is_full(&handle)){
            float a = 0;
            queue_remove(&handle, &a);
            sum -= a;
        }
        queue_insert(&handle, in[i]);
        sum += in[i];
        out[i] = sum / (float)queue_get_len(&handle);
    }
}

/**
 * @brief Parses data from file to float values.
 * @param[in] n
 * @param[in] data Must be at least of size n.
 * @param[out] values Must be valid, cannot be NULL.
 * @return Number of parsed values.
 * @note Must be optimized, now it goes through all data chars all over again. Maybe it can be merged with reading?
*/
size_t parse_data(size_t n, char data[static n], float values[static 1])
{
    size_t val_cnt = 0;
    for(char* ptr_data = &data[0]; ptr_data < &data[n]; /* 3rd arg not present */){
        if(isdigit(*ptr_data) > 0){
            values[val_cnt] = strtof(ptr_data, &ptr_data);
            // logger("%.2f\n", values[val_cnt]);
            val_cnt++;
        }else{
            ptr_data++;
        }
    }
    return val_cnt;
}

/**
 * @brief Reads data from file, if it cannot read all file, it reads a chunk.
 * @param[in] filename Must be valid, cannot be NULL.
 * @param[in] offset Used if previous readout could not fit entirely.
 * @param[in] n
 * @param[in] data Must be at least of size n.
 * @return Bytes that was read from file. -1 if failed.
*/
size_t read_file(char filename[static 1], size_t offset, size_t n, char data[static n]){
    if(strlen(filename) > FILENAME_MAX){
        return -1;
    }
    
    FILE* data_file = fopen(filename, "r");
    if(data_file == NULL){
        logger("could not open file.\n");
        return -1;
    }

    /* Check the size of file, whether it fits into data or not. */
    fseek(data_file, 0L, SEEK_END);
    size_t bytes_to_read = ftell(data_file);
    if(bytes_to_read > n){
        logger("file cannot fit. Aborting");
        return -1;
    }
    rewind(data_file);
    
    size_t i;
    for(i = 0; i < bytes_to_read; i++){
        int ch = fgetc(data_file);
        if(ch == EOF){
            break;
        }
        data[i] = ch;
    }
    return i;
}


int main(int argc, char** argv){
    if(argc < ARGV_REQUIRED){
        logger("Usage: ./trumpf_zadanie <path_to_csv_file>\n");
        return EXIT_FAILURE;
    }
    char data[DATA_CHUNK_SIZE] = {0};
    size_t bytes_read = read_file(argv[1], 0, DATA_CHUNK_SIZE, data);
    if(bytes_read == -1){
        return EXIT_FAILURE;
    }
    float values[VALUES_COLUMNS][VALUES_CHUNK_SIZE] = {0};
    size_t values_cnt = parse_data(bytes_read, data, &values[0][0]);
    
    #ifdef PARSING_DATA_LOG
    for(size_t i = 0; i < values_cnt; i++){
        logger("%.2f\n", values[0][i]);
    }
    #endif
    moving_average(MOVING_WINDOW_SIZE, values_cnt, &values[0][0], &values[1][0]);
    moving_max(MOVING_WINDOW_SIZE, values_cnt, &values[0][0], &values[2][0]);
    moving_min(MOVING_WINDOW_SIZE, values_cnt, &values[0][0], &values[3][0]);
    FILE* out_file = fopen("out.csv", "w");
    fprintf(out_file, "data\tmoving_avg\tmoving_max\tmoving_min\n");
    for(size_t i = 0; i < values_cnt; i ++){
        fprintf(out_file, "%.2f\t%.2f\t\t%.2f\t\t%.2f\n", values[0][i], values[1][i], values[2][i], values[3][i]);
    }
    fprintf(out_file, "\n");
    return EXIT_SUCCESS;
}