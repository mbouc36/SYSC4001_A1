#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interrupts.h"
#include <unistd.h>
#include <sys/time.h> 


//switches user modes (1 ms)
void switch_user_modes(int *current_time, FILE *execution_file){
    usleep(1*1000);
    fprintf(execution_file, "%d, %d, switch to kernel mode\n", *current_time, 1);
    *current_time += 1; 
}

//saves and restores context (1-3 ms random)
void save_restore_context(int *current_time, FILE *execution_file){
    int min = 1;
    int max = 3;

    // Generate a random number between 1 and 3
    int randomInt = rand() % (max - min + 1) + min;
    usleep(randomInt*1000);
    fprintf(execution_file, "%d, %d, context saved\n", *current_time, randomInt);
    *current_time += randomInt;
}

// calculates where in memory the ISR starts (1ms)
void get_ISR_start_address(int *current_time, unsigned int vector_table_address, FILE *execution_file){
    usleep(1*1000);
    fprintf(execution_file, "%d, %d, find vector %d in memory position 0x%04x\n", *current_time, 1, vector_table_address, vector_table_address * 2); // memeory position is vector number in hex + 0x2
    *current_time += 1; 
}


//get the address if the ISR from the vector table (1 ms)
void load_vector_address_to_pc(int *current_time, unsigned int ISR_address, FILE *execution_file){
    usleep(1*1000);
    fprintf(execution_file, "%d, %d, load address 0x%04x into the PC\n", *current_time, 1, ISR_address);
    *current_time += 1; 
}

//get ISR start address, address from vector table, execute the instructions for the ISR (ISR execute time +1 +1)
//This needs to be completelty redone
void execute_ISR(int *current_time, int ISR_duration, FILE *execution_file){
    if (ISR_duration > 1000){
        sleep(ISR_duration/1000);
    } else {
        usleep(ISR_duration*1000);
    }

    fprintf(execution_file, "%d, %d, SYSCALL: run the ISR\n", *current_time, ISR_duration * 50 / 100);
    *current_time += ISR_duration * 0.50;
    fprintf(execution_file, "%d, %.d, transfer data\n", *current_time, ISR_duration * 40 / 100);
    *current_time += ISR_duration * 0.40;
    fprintf(execution_file, "%d, %.d, check for errors\n", *current_time, ISR_duration - ISR_duration * 50 / 100 - ISR_duration * 40 / 100);

    *current_time += ISR_duration - ISR_duration * 50 /100 - ISR_duration * 40 / 100;
}

//Return the value from the interrupt subroutine ( 1ms)
void IRET(int *current_time, FILE *execution_file){
    usleep(1*1000);
    fprintf(execution_file, "%d, %d, IRET\n", *current_time, 1);
    *current_time += 1; 

}


//Handles the end of I/O situation
void end_of_IO(int *current_time, int ISR_duration, FILE *execution_file){
    if (ISR_duration > 1000){
        sleep(ISR_duration/1000);
    } else {
        usleep(ISR_duration*1000);
    }
    fprintf(execution_file, "%d, %d, END_IO\n", *current_time, ISR_duration);
    *current_time += ISR_duration;
}


//checks interrupt pritority
void check_priority_of_ISR(int *current_time, FILE *execution_file){
    usleep(1*1000);
    fprintf(execution_file, "%d, %d, check priority of interrupt\n", *current_time, 1);
    *current_time += 1; 
}

//check if ISR is masked
void check_if_masked(int *current_time, FILE *execution_file){
    usleep(1*1000);
    fprintf(execution_file, "%d, %d, check if masked\n", *current_time, 1);
    *current_time += 1; 
}



//represetns efforts by the cpu, duration obtained from trace.txt
void cpu_execution(int *current_time, int duration, FILE *execution_file){
    if (duration > 1000){
        sleep(duration/1000);
    } else {
        usleep(duration*1000);
    }
    fprintf(execution_file, "%d, %d, CPU execution\n", *current_time, duration);
    *current_time += duration;
}

int main(int argc, char *argv[]){
    if (argc > 4){
        printf("Too many command line inputs");
    }

    FILE  *trace_file, *vector_table, *execution_file, *time_file;

    char line[256];
    int vector_table_array[100]; // we use this array to store the vector table
    unsigned int value;
    char operation[20];
    int duration, vector_number;
    int current_time = 0;

    time_file = fopen("time_data.txt", "w"); // write to timer file 
    if(time_file == NULL){
        printf("can't open\n");
        return 1;
    }
 
    char *vector_table_name = argv[2];
    vector_table = fopen(vector_table_name, "r");


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


    //Let's prepare the output file
    char *execution_file_name = argv[3];
    execution_file = fopen(execution_file_name, "w");
    if (execution_file == NULL) {
        printf("Error opening file.\n");
        return 1;  //If file couldn't open
    }

    char *filename = argv[1];
    // Now that we've loaded the vector table let's start parsing the trace file
    trace_file = fopen(filename,"r");
    

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
                syscall_count++;
                struct timeval syscall_start, syscall_end;
                gettimeofday(&syscall_start, NULL);
                
                switch_user_modes(&current_time, execution_file);
                save_restore_context(&current_time, execution_file);
                get_ISR_start_address(&current_time, vector_number, execution_file);
                load_vector_address_to_pc(&current_time, vector_table_array[vector_number], execution_file);
                execute_ISR(&current_time, duration, execution_file);
                IRET(&current_time, execution_file);
                
                gettimeofday(&syscall_end, NULL);
                double syscall_total_time = (syscall_end.tv_sec - syscall_start.tv_sec) * 1000.0 + 
                                            (syscall_end.tv_usec - syscall_start.tv_usec) / 1000.0;
                total_overhead_time += syscall_total_time;
                total_cpu_time += duration;
                fprintf(time_file, "SYSCALL, %.6f\n", syscall_total_time);
                fflush(time_file);
                

            } else if (strcmp(operation, "END_IO") == 0){
                end_io_count++;
                

                struct timeval end_io_start, end_io_end;
                gettimeofday(&end_io_start, NULL);

                check_priority_of_ISR(&current_time, execution_file);
                check_if_masked(&current_time, execution_file);
                switch_user_modes(&current_time, execution_file);
                save_restore_context(&current_time, execution_file);
                get_ISR_start_address(&current_time, vector_number, execution_file);
                load_vector_address_to_pc(&current_time, vector_table_array[vector_number], execution_file);
                end_of_IO(&current_time, duration, execution_file);
                IRET(&current_time, execution_file);

                gettimeofday(&end_io_end, NULL);
                double total_end_io = (end_io_end.tv_sec - end_io_start.tv_sec) * 1000.0 + 
                                      (end_io_end.tv_usec - end_io_start.tv_usec) / 1000.0;
                total_overhead_time += total_end_io;
                total_io_time += duration;
                fprintf(time_file, "END_IO, %.6f\n", total_end_io);
                fflush(time_file);

            }
             
        } else if (sscanf(line, "%[^,], %d", operation, &duration) == 2) { // 2 because this is the number of variables returned
            //This is a cpu function
            if (strcmp(operation, "CPU") == 0){
                cpu_execution(&current_time, duration, execution_file);
            }
           
        }else {
            printf("Failed to parse line: %s", line);
        }
    }

    // summary of time 
    fprintf(time_file, "------SUMMARY------\n");
    fprintf(time_file, "Total CPU Time: %.3f ms\n", total_cpu_time);
    fprintf(time_file, "Total I/O Time: %.3f ms\n", total_io_time);
    fprintf(time_file, "Total Overhead Time: %.3f ms\n", total_overhead_time);

    double total_time = total_cpu_time + total_io_time + total_overhead_time;

    if (total_time > 0) {
        fprintf(time_file, "CPU Usage Ratio: %.2f%%\n", (total_cpu_time / total_time) * 100);
        fprintf(time_file, "I/O Activity Ratio: %.2f%%\n", (total_io_time / total_time) * 100);
        fprintf(time_file, "Overhead Ratio: %.2f%%\n", (total_overhead_time / total_time) * 100);
    } else {
        fprintf(time_file, "No CPU or I/O time recorded, cannot calculate ratios.\n");
    }

    
    fclose(trace_file);
    fclose(execution_file);
    fclose(time_file);                        
    return 0;

}

