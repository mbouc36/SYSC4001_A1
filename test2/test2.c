#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int test2();

int test2(){


 FILE *trace_file, *real_output;
    int syscall_array[100]; //stores all the sys calls
    char syscall_line[256];
    char real_line[256];
    char real_event[50];
    char value[30]; //used to read the syscall line
    int desired_ISR_duration = 0;
    int real_ISR_duration = 0; 
    int duration = 0 ; //duration  of the current event
    int ISR_step = 0; //used to check which step of the ISR we are on ( SYSCALL: run the ISR, transfer data, check for errors)

    

    //read trace file as input, we only want to read the sys calls and their durations
    //read each line of the execution file untill we encouter a syscall, count the duration of the total sys call (SYSCALL, transfer data, erro checking)
    //compare to syscall index in syscall array
    
    
    real_output = fopen("execution.txt", "r");
    trace_file = fopen("trace.txt", "r");

    if (NULL == trace_file){
        printf("Desired output file can't open\n");
        return 0;
    }

    if (NULL == real_output){
        printf("Real output file can't open\n");
        return 0;
    }

    unsigned char bom[3];
    if (fread(bom, 1, 3, trace_file) == 3) {
        if (bom[0] != 0xEF || bom[1] != 0xBB || bom[2] != 0xBF) {
            fseek(trace_file, 0, SEEK_SET);
        }
    }

  
    if (fread(bom, 1, 3, real_output) == 3) {
        if (bom[0] != 0xEF || bom[1] != 0xBB || bom[2] != 0xBF) {
            fseek(real_output, 0, SEEK_SET);
        }
    }
    
    int i = 0 ;
    // Read the file line by line
    while (fgets(syscall_line, sizeof(syscall_line), trace_file)) {
        // Convert the hex string to an integer
        sscanf(syscall_line, "%d, %*d, %s",&desired_ISR_duration, value);
        if (strcmp(value, "SYSCALL:")) {
            syscall_array[i] = desired_ISR_duration;
            i++;
        } else {
            printf("Failed to parse line");
        }
    }
    while (fgets(real_line, sizeof(real_line), real_output)){
        //%*d reads the int but discards it because we are only looking for the string
        // the reason we are using %[^\n] here is because sscanf will stop reading after a space, therefore we won't get the while line
        sscanf(real_line, "%d, %*d, %s",&duration, real_event);
        

        //checks if the line is a sys call
        if (strcmp(real_event, "SYSCALL:") == 0 && ISR_step == 0){
            real_ISR_duration += duration;
            ISR_step++;

        } else if (strcmp(real_event, "transfer") && ISR_step == 1){
            real_ISR_duration += duration;
            ISR_step++;
        } else if (strcmp(real_event, "transfer") && ISR_step == 1){
            real_ISR_duration += duration;
            ISR_step++;
            if (real_ISR_duration != desired_ISR_duration){
                printf("Error totalling ISR values");
                return 0;
            }
            ISR_step = 0;
            real_ISR_duration = 0;
        }
        
  
    }
    fclose(trace_file);
    fclose(real_output);

    printf("\nTest 2 Passed successfully\n");

    return 0;
}