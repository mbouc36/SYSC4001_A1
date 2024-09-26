#include "fxns.h"

//switches user modes (1 ms)
void switch_user_modes(int *current_time){
    printf("%d, %d, switch to kernel mode\n", *current_time, 1);
    *current_time++; 
}

//saves and restores context (1-3 ms random)
void save_restore_context(int *current_time){
    int min = 1;
    int max = 3;

    // Generate a random number between 10 and 30
    int randomInt = rand() % (max - min + 1) + min;
    printf("%d, %d, context saved\n", *current_time, randomInt);
    *current_time += randomInt;
}

// calculates where in memory the ISR starts (1ms)
void get_ISR_start_address(int *current_time, unsigned int vector_table_address){
    printf("%d, %d, Find vector %d in position 0x%x\n", *current_time, 1, vector_table_address, vector_table_address * 2); // memeory position is vector number in hex + 0x2
    *current_time++; 
}


//get the address if the ISR from the vector table (1 ms + duration of ISR)
void load_vector_address_to_pc(int *current_time, unsigned int ISR_address){
    printf("%d, %d, load address 0x%x into the PC\n", *current_time, 1, ISR_address);
    *current_time++; 
}

//get ISR start address, address from vector table, execute the instructions for the ISR (ISR execute time +1 +1)
//This needs to be completelty redone
void execute_ISR(int *current_time, float ISR_duration){

    printf("%d, %.0f, SYSCALL: run the ISR\n", *current_time, ISR_duration * 0.50);
    *current_time += ISR_duration * 0.50;
    printf("%d, %.0f, transfer data\n", *current_time, ISR_duration * 0.40);
    *current_time += ISR_duration * 0.40;
    printf("%d, %.0f, check for errors\n", *current_time, ISR_duration - ISR_duration * 0.50 - ISR_duration * 0.40);

    *current_time += ISR_duration - ISR_duration * 0.50 - ISR_duration * 0.40;
}

//Return the value from the interrupt subroutine ( 1ms)
void IRET(int *current_time){
    printf("%d, %d, IRET\n", *current_time, 1);
    current_time += 1;
    *current_time++; 

}


//Handles the end of I/O situation
void end_of_IO(int *current_time, int ISR_duration){

    printf("%d, %d, END_IO\n", *current_time, ISR_duration);

    *current_time += ISR_duration;
}


//checks interrupt pritority
void check_priority_of_ISR(int *current_time){
    printf("%d, %d, check priority of interrupt\n", *current_time, 1);
    *current_time++; 
}

//check if ISR is masked
void check_if_masked(int *current_time){
    printf("%d, %d, check if masked\n", *current_time, 1);
    *current_time++; 
}



//represetns efforts by the cpu, duration obtained from trace.txt
void cpu_execution(int *current_time, int duration){
    printf("%d, %d, cpu execution \n", *current_time, duration);
    *current_time += duration;
}