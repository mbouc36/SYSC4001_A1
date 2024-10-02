
#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <stdio.h>
#include <stdlib.h> 

//switches user modes (1 ms)
void switch_user_modes(int *current_time, FILE *execution_file);

//saves and restores context (1-3 ms random)
void save_restore_context(int *current_time, FILE *execution_file); 

// calculates where in memory the ISR starts (1ms)
void get_ISR_start_address(int *current_time, unsigned int vector_table_address, FILE *execution_file);

//get the address if the ISR from the vector table (1 ms)
void load_vector_address_to_pc(int *current_time, unsigned int ISR_address, FILE *execution_file);

//execute the instructions for the ISR (duration found from input on vector table)
void execute_ISR(int *current_time, int ISR_duration, FILE *execution_file);

//Return the value from the interrupt subroutine ( 1ms)
void IRET(int *current_time, FILE *execution_file);

//Handles the end of I/O situation
void end_of_IO(int *current_time, int ISR_duration, FILE *execution_file);

//checks interrupt pritority
void check_priority_of_ISR(int *current_time, FILE *execution_file);

//check if ISR is masked
void check_if_masked(int *current_time, FILE *execution_file);

//represetns efforts by the cpu, duration obtained from trace.txt
void cpu_execution(int *current_time, int duration, FILE *execution_file);

#endif