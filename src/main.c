#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "logger.h"
#include "float_queue.h"

#define ARGV_REQUIRED 2U
#define DATA_CHUNK_SIZE 8096U
#define VALUES_CHUNK_SIZE 1024U
#define MOVING_WINDOW_SIZE 3U
#define VALUES_COLUMNS 4U




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
    for(size_t i = 0; i < values_cnt; i++){
        logger("%.2f\n", values[0][i]);
    }
    return EXIT_SUCCESS;
}