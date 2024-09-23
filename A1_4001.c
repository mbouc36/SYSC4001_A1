#include <stdio.h>
#include <string.h>


FILE *trace_file, *execution_file;

char activities[100][50]; // To store activity names is max 50, only 100 activities allowed 
int addresses[100];        // To store addresses
int durations[100];        // To store durations
int num_of_activities = 0;
int time_of_event = 0;

void logEvent(int time_of_event, int duration, const char *event_type) {
    fprintf(execution_file, "%d %d %s\n", time_of_event, duration, event_type);
}

void loadTrace(FILE *trace_file) {
    char line[100];

    
    fgets(line, sizeof(line), trace_file);

    while (fgets(line, sizeof(line), trace_file) != NULL) {
        
        if (sscanf(line, "%[^,], %d, %d", activities[num_of_activities], &addresses[num_of_activities], &durations[num_of_activities]) == 3) {
            num_of_activities++;
        }
    }
}

void process_cpu() {
    for (int i = 0; i < num_of_activities; i++) {
        if (strcmp(activities[i], "CPU") == 0) {
            logEvent(time_of_event, durations[i], "CPU Processing");
            time_of_event += durations[i]; // Update time_of_event
            break;
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

    for (int i = 0; i < num_of_activities; i++) {
        if (strcmp(activities[i], "CPU") == 0) {
            process_cpu();
        }
    }

    fclose(execution_file);
    return 0;
}
