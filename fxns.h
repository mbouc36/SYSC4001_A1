#include <stdio.h>
#include <stdlib.h> 
#ifndef FXNS_H
#define FXNS_H
#endif

//switches user modes (1 ms)
int switch_user_modes(int current_time);

//saves and restores context (1-3 ms random)
int save_restore_context(int current_time); 

// calculates where in memory the ISR starts (1ms)
int get_ISR_start_address(int current_time, int vector_table_address, int memory_position);

//get the address if the ISR from the vector table (1 ms)
int get_ISR_address_from_vector_table(int current_time);

//execute the instructions for the ISR (duration found from input on vector table)
int execute_ISR(int current_time, int vector_table_addres, int vector_table[4][4]);

//Return the value from the interrupt subroutine ( 1ms)
int IRET(int current_time);

//Handles the end of I/O situation
int end_of_IO(int current_time, int vector_table_addres, int vector_table[4][4]);
