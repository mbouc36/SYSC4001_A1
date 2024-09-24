#include "fxns.h"

//switches user modes (1 ms)
int switch_user_modes(int current_time){
    printf("%d, %d, Switch User modes", current_time, 1);
    current_time += 1;
    return 1;
}

//saves and restores context (1-3 ms random)
int save_restore_context(int current_time){
    int min = 1;
    int max = 3;

    // Generate a random number between 10 and 30
    int randomInt = rand() % (max - min + 1) + min;
    printf("%d, %d, context saved/restored", current_time, randomInt);
    current_time += randomInt;
    return randomInt;
}

// calculates where in memory the ISR starts (1ms)
int get_ISR_start_address(int current_time, int vector_table_address, int memory_position){
    printf("%d, %d, Find vector %d in position %d", current_time, 1, vector_table_address, memory_position);
    current_time += 1;
    return 1;
}

//get the address if the ISR from the vector table (1 ms + duration of ISR)
int get_ISR_address_from_vector_table(int current_time){
    printf("%d, %d, Obtain ISR address", current_time, 1);
    current_time += 1;
    return 1; 
}

//get ISR start address, address from vector table, execute the instructions for the ISR (ISR execute time +1 +1)
int execute_ISR(int current_time, int vector_table_address, int vector_table[4][4]){
    float ISR_duration;
    int memory_position;
    for (int i = 0;  i < 4; i++ ){
        if (vector_table[i][1] == vector_table_address){
            ISR_duration = vector_table[i][3];
            memory_position = vector_table[i][2];
            
        }
    }
    get_ISR_start_address(current_time, vector_table_address, memory_position);
    get_ISR_address_from_vector_table(current_time);


    printf("%d, %.0f, call device driver", current_time, ISR_duration * 0.40);
    current_time += ISR_duration * 0.40;
    printf("%d, %.0f, transfer data", current_time, ISR_duration * 30);
    current_time += ISR_duration * 0.30;
    printf("%d, %.0f, check for errors", current_time, ISR_duration - ISR_duration * 0.40 - ISR_duration * 30);
    current_time += ISR_duration - ISR_duration * 0.40 - ISR_duration * 30;

    return ISR_duration;
}

//Return the value from the interrupt subroutine ( 1ms)
int IRET(int current_time){
    printf("%d, %d, exectute ISR", current_time, 1);
    current_time += 1;
    return 1;
}


//Handles the end of I/O situation
int end_of_IO(int current_time, int vector_table_address, int vector_table[4][4]){
    int ISR_duration;

    for (int i = 0;  i < 4; i++ ){
        if (vector_table[i][1] == vector_table_address){
            ISR_duration = vector_table[i][3];            
        }
    }
    printf("%d, %d, end of I/O %d", current_time, ISR_duration, vector_table_address);

    return ISR_duration;
}
