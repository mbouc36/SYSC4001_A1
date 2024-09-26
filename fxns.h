#include <stdio.h>
#include <stdlib.h> 
#ifndef FXNS_H
#define FXNS_H
#endif

//switches user modes (1 ms)
void switch_user_modes(int *current_time);

//saves and restores context (1-3 ms random)
void save_restore_context(int *current_time); 

// calculates where in memory the ISR starts (1ms)
void get_ISR_start_address(int *current_time, unsigned int vector_table_address);

//get the address if the ISR from the vector table (1 ms)
void load_vector_address_to_pc(int *current_time, unsigned int ISR_address);

//execute the instructions for the ISR (duration found from input on vector table)
void execute_ISR(int *current_time, float ISR_duration);

//Return the value from the interrupt subroutine ( 1ms)
void IRET(int *current_time);

//Handles the end of I/O situation
void end_of_IO(int *current_time, int ISR_duration);

//This functions contains all interrupt events
void handle_interrupt(int *current_time);

//checks interrupt pritority
void check_priority_of_ISR(int *current_time);

//check if ISR is masked
void check_if_masked(int *current_time);

//represetns efforts by the cpu, duration obtained from trace.txt
void cpu_execution(int *current_time, int duration);