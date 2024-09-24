#include <stdio.h>
#include <string.h>


FILE *trace_file, *execution_file;

char activities[100][50]; // To store activity names is max 50, only 100 activities allowed 
//int addresses[100];        // To store addresses
int durations[100];        // To store durations
int num_of_activities = 0;
int time_of_event = 0;

int vector_table[4][4] = {{0, 7, 14, 110},
                          {0, 12, 24, 250}, 
                          {0, 20, 40, 170},
                          {0, 22, 22, 328}};




void logEvent(int time_of_event, int duration, const char *event_type) { // func takes the time of the event, duration and the event type and write it in execution file
    fprintf(execution_file, "%d %d %s\n", time_of_event, duration, event_type);
}

void loadTrace(FILE *trace_file) { // load the trace file 
    char line[100];
    fgets(line, sizeof(line), trace_file); // read each line 

    while (fgets(line, sizeof(line), trace_file) != NULL) {
        
        if (sscanf(line, "%[^,], %d", activities[num_of_activities],  &durations[num_of_activities]) == 2) { //seperate the activitiy and the duration 
            
            num_of_activities++; // each line read the num of activities increment 
        }
    }
}

void process_cpu() {
    for (int i = 0; i < num_of_activities; i++) { // function is to mainly process cpu, itertae over the activities read so far
        if (strcmp(activities[i], "CPU") == 0) { // search for CPU activity
            logEvent(time_of_event, durations[i], "CPU Processing"); // log it to execution file
            time_of_event += durations[i]; // Update time_of_event
        }
    }
}

int main() {
    trace_file = fopen("trace.txt", "r"); // Open the file
    if (trace_file == NULL) {
        printf("Error opening trace file");
        return 1; // Exit if file opening fails
    }

    execution_file = fopen("execution.txt", "w"); // Log the events
    if (execution_file == NULL) {
        printf("Error opening execution file");
        fclose(trace_file);
        return 1; // Exit if file opening fails
    }

    loadTrace(trace_file);
    fclose(trace_file);

    process_cpu(); //call the cpu function

    fclose(execution_file);
    return 0;
}
