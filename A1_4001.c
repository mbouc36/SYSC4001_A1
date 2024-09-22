#include <string.h>
#include <stdlib.h>
#include <stdio.h>
FILE *trace_file, *execution_file, *vector_table;

    char line[100];
    char activity[50];
    int duration;
    int time_of_event = 0;
    const char event_type;
// function to log the events into execution file 
logEvent(execution_file, time_of_event, duration, event_type){
    fprintf(execution_file, "%d %d %s\n", time_of_event, duration, event_type);
    time_of_event+=duration;
}
/ functions to handle inteerupts 
void HandleInterrupt(int ISRtime, FILE *execution_file, int time_of_event){
    logEvent(execution_file, time_of_event, switch_user_modes());
    logEvent();
    

}

int main(){

    trace_file = fopen("trace.txt", "r"); //open the file
    execution_file = fopen("execution.txt","w"); // log the events
    vector_table = fopen("VectorTable", "r"); // access the vector table when there's a systems call 


    if (trace_file != NULL){ // see if the file is not empty
        while (fgets(line,sizeof(line),trace_file) != NULL){ // take line by line and using sizeof to make sure it doesnt exceed the capacity of line array
            if (sscanf(line,"%49[^,], %d",activity, &duration) == 2){ // seperate activity and duration ro compare the activity
                if(strcmp(activity,"CPU")== 0){ // compare if the activity is CPU 
                    // if it is CPU log it into execution file and add the duration
                    printf("CPU found\n"); // just to cehck the code 


                }
            }
        }
    }
    fclose(trace_file);
    fclose(execution_file);
    fclose(vector_table);
    return 0;
}
