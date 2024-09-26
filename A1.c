#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fxns.h"

int main(){
    FILE  *trace_file, *vector_table, *execution_file;

    char line[256];
    int vector_table_array[100]; // we use this array to store the vector table
    unsigned int value;
    char operation[20];
    int duration, vector_number;
    int current_time = 0;
 

    vector_table = fopen("vector_table.txt", "r");


    if (NULL == vector_table){
        printf("File can't open\n");
        return 0;

    }
    //first let's read the vector table and store it
    //the below function is used to skip the intially reading the file is UTF-8 encoded
    unsigned char bom[3];
    if (fread(bom, 1, 3, vector_table) == 3) {
        if (bom[0] != 0xEF || bom[1] != 0xBB || bom[2] != 0xBF) {
            fseek(vector_table, 0, SEEK_SET);
        }
    }

    int i = 0 ;
    // Read the file line by line
    while (fgets(line, sizeof(line), vector_table)) {
        // Convert the hex string to an integer
        if (sscanf(line, "%x", &value) == 1) {
            vector_table_array[i] = value;
            i++;
        } else {
            printf("Failed to parse line: %s", line);
        }
    }

    // Now that we've loaded the vector table let's start parsing the trace file
    trace_file = fopen("trace.txt","r");
    

    if (NULL == trace_file){
        printf("File can't open\n");
        return 0;

    }

    //the below function is used to skip the intially reading the file is UTF-8 encoded
    if (fread(bom, 1, 3, trace_file) == 3) {
        if (bom[0] != 0xEF || bom[1] != 0xBB || bom[2] != 0xBF) {
            fseek(trace_file, 0, SEEK_SET);
        }
    }
      // Read the file line by line
    while (fgets(line, sizeof(line), trace_file)) {
         if (sscanf(line, "%s %d, %d", operation, &vector_number, &duration) == 3) {
            //This is either a SYSCALL or END_IO
            if (strcmp(operation, "SYSCALL") == 0){
                switch_user_modes(&current_time);
                save_restore_context(&current_time);
                get_ISR_start_address(&current_time, vector_number);
                load_vector_address_to_pc(&current_time, vector_table_array[vector_number]);
                execute_ISR(&current_time, duration);
                IRET(&current_time);

            } else if (strcmp(operation, "END_IO") == 0){
                check_priority_of_ISR(&current_time);
                check_if_masked(&current_time);
                switch_user_modes(&current_time);
                save_restore_context(&current_time);
                get_ISR_start_address(&current_time, vector_number);
                load_vector_address_to_pc(&current_time, vector_table_array[vector_number]);
                end_of_IO(&current_time, duration);
                IRET(&current_time);
            }
        } else if (sscanf(line, "%[^,], %d", operation, &duration) == 2) { // 2 because this is the number of variables returned
            //This is a cpu function
            if (strcmp(operation, "CPU") == 0){
                cpu_execution(&current_time, duration);
            }
           
        }else {
            printf("Failed to parse line: %s", line);
        }
    }
    fclose(trace_file);
    


    // read line determine type (CPU, SYSCALL, END_IO)      TODO: ask TA abt breakdown for CPU and END_IO
    // place updated time on output and add function and duration

    //current implementation loads input into an array, couldn't I just read directly
    // yep we can used fscanf/ fgetc() they return EOF when end of file




                          
                          
    return 0;

}

