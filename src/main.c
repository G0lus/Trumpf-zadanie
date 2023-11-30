#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATA_MAX_SIZE 8096U
#define VALUES_MAX_SIZE 2048U
#define VALUES_COLUMNS 4U
#define ARGV_REQUIRED 3U

#include "logger.h"
#include "float_queue.h"

void moving_max(size_t n, float in[static n], float out[static n]){
    queue_handle handle = queue_init();
    for(size_t i = 0; i < n; i++){
        if(queue_is_full(&handle)){
            queue_remove(&handle, NULL);
        }
        queue_insert(&handle, in[i]);
        out[i] = queue_get_max(&handle);
    }
}

void moving_min(size_t n, float in[static n], float out[static n]){
    queue_handle handle = queue_init();
    for(size_t i = 0; i < n; i++){
        
        if(queue_is_full(&handle)){
            queue_remove(&handle, NULL);
        }
        queue_insert(&handle, in[i]);
        out[i] = queue_get_min(&handle);
    }
}

void moving_average(size_t n, float in[static n], float out[static n]){
    queue_handle handle = queue_init();
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
    fclose(data_file);
    return i;
}

/**
 * @param[in] filename  Name of the file to write to (with extension)
 * @param[in] max_row   Max number of rows to print to file
 * @param[in] col   Columns of the data array
 * @param[in] row   Rows of the data array
 * @param[in] data  Col-dimensional array with values to print.
 * @return number of bytes written to file or -1 if error opening file.
 * @warning Providing the name of the file that already exists will overwrite it.
*/
size_t save_file(char filename[static 1], size_t max_row, size_t col, size_t row, float* data){
    FILE* out_file = fopen(filename, "w");
    if(!out_file){
        perror("Cannot open file");
    }
    fprintf(out_file, "data;moving_avg;moving_max;moving_min;\n");
    for(size_t r = 0; r < max_row; r++){
        for(size_t c = 0; c < col; c++){
            fprintf(out_file, "%.2f;", data[c*row + r]);
        }
        fprintf(out_file, "\n");
    }
    fclose(out_file);
    return col*max_row;
}

int main(int argc, char** argv){
    if(argc < ARGV_REQUIRED){
        logger("Usage: ./trumpf_zadanie <path_to_input_csv_file> <path_to_output_csv_file\n");
        return EXIT_FAILURE;
    }
    char data[DATA_MAX_SIZE] = {0};
    size_t bytes_read = read_file(argv[1], 0, DATA_MAX_SIZE, data);
    if(bytes_read == -1){
        return EXIT_FAILURE;
    }
    float values[VALUES_COLUMNS][VALUES_MAX_SIZE] = {0};
    size_t values_cnt = parse_data(bytes_read, data, &values[0][0]);
    
    #ifdef PARSING_DATA_LOG
    for(size_t i = 0; i < values_cnt; i++){
        logger("%.2f\n", values[0][i]);
    }
    #endif

    moving_average(values_cnt, &values[0][0], &values[1][0]);
    moving_max(values_cnt, &values[0][0], &values[2][0]);
    moving_min(values_cnt, &values[0][0], &values[3][0]);
    
    save_file(argv[2], values_cnt, VALUES_COLUMNS, VALUES_MAX_SIZE, &values[0][0]);
    return EXIT_SUCCESS;
}