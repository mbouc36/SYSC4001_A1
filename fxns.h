#include <stdio.h>
#include <stdlib.h> 

//switches user modes (1 ms)
int switch_user_modes();

//saves and restores context (1-3 ms random)
int save_restore_context(); 

// calculates where in memory the ISR starts (1ms)
int get_ISR_start_address();

//get the address if the ISR from the vector table (1 ms)
int get_ISR_address_from_vector_table(int vector_table_address, int vector_table[3][3], int vector_table_size_h, int vector_table_size_w);

//execute the instructions for the ISR (duration found from input on vector table)
int execute_ISR(int vector_table_address);

//Return the value from the interrupt subroutine ( 1ms)
int IRET();

//This function represetns the time it takes to initialize the program (50 ms)
int initalize_program();

//Value calculation (100 ms)
int update_counter();

//this represents the time it takes to return after the final END_IO
int handle_loop();
