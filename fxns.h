#include <stdio.h>
#include <stdlib.h> 

//switches user modes (1 ms)
int switch_user_modes();

//saves and restores context (10-30 ms random)
int save_restore_context(); 

// calculates where in memory the ISR starts (1ms)
int get_ISR_start_address();

//get the address if the ISR from the vector table (1 ms)
int get_ISR_address_from_vector_table();

//execute the instructions for the ISR (20-40ms)
int execute_ISR();

//Return the value from the interrupt subroutine ( 1ms)
int IRET();
