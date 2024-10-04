#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// This test file simply tests that the times are added correctly and that the sequence of desired_events are printed in the correct order
// note this test will fail if a different vector table is used from the one provided 

//1. leading zeros in vector address
//2. 

int test1();

int test1(){

    FILE *desired_output, *real_output;

    char desired_line[256];
    char real_line[256];
    int duration;
    int prev_time = 0;
    int prev_duration = 0;
    int current_time = 0;
    char desired_event[50];
    char real_event[50];
    
    real_output = fopen("execution.txt", "r");
    desired_output = fopen("test1/test1_execution.txt", "r");

    if (NULL == desired_output){
        printf("Desired output file can't open\n");
        return 0;
    }

    if (NULL == real_output){
        printf("Real output file can't open\n");
        return 0;
    }

    unsigned char bom[3];
    if (fread(bom, 1, 3, desired_output) == 3) {
        if (bom[0] != 0xEF || bom[1] != 0xBB || bom[2] != 0xBF) {
            fseek(desired_output, 0, SEEK_SET);
        }
    }

  
    if (fread(bom, 1, 3, real_output) == 3) {
        if (bom[0] != 0xEF || bom[1] != 0xBB || bom[2] != 0xBF) {
            fseek(real_output, 0, SEEK_SET);
        }
    }
    
    while (fgets(desired_line, sizeof(desired_line), desired_output) != NULL && fgets(real_line, sizeof(real_line), real_output) != NULL){
        prev_time = current_time;
        //%*d reads the int but discards it because we are only looking for the string
        // the reason we are using %[^\n] here is because sscanf will stop reading after a space, therefore we won't get the while line
        sscanf(real_line, "%*d, %*d, %[^\n]", real_event);
        sscanf(desired_line, "%d, %d, %[^\n]", &current_time, &duration, desired_event);

        if (strcmp(desired_event, real_event) != 0){        
            printf(real_event);
            printf(desired_event);
            printf("The event names do not match up");

            return 0;

        }   else if (current_time != prev_time + prev_duration){
            printf("Error adding times");
            return 0;
        }
        prev_time = current_time;
        prev_duration = duration;

    }
    fclose(desired_output);
    fclose(real_output);

    printf("\nTest 1 Passed successfully\n");
    return 0;
}



