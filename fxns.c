//switches user modes (1 ms)
int switch_user_modes(){
    return 1;
}

//saves and restores context (1-3 ms random)
int save_restore_context(){
    int min = 1;
    int max = 3;

    // Generate a random number between 10 and 30
    int randomInt = rand() % (max - min + 1) + min;
    return randomInt;
}

// calculates where in memory the ISR starts (1ms)
int get_ISR_start_address(){
    return 1;
}

//get the address if the ISR from the vector table (1 ms + duration of ISR)
int get_ISR_address_from_vector_table(int vector_table_address){
    return 1; 
}

//execute the instructions for the ISR (20-40ms)
int execute_ISR(int vector_table_address, int vector_table[3][3], int vector_table_size_h, int vector_table_size_w){
    int ISR_duration;
    for (int i = 0;  i < vector_table_size_h; i++ ){
        if (vector_table[i][1] == vector_table_address){
            ISR_duration = vector_table[i][3];
        }
    }
    return ISR_duration;
}

//Return the value from the interrupt subroutine ( 1ms)
int IRET(){
    return 1;
}

//This function represetns the time it takes to initialize the program (50 ms)
int initalize_program(){
    return 50;
}

//Value calculation (100 ms)
int update_counter(){
    return 100;
}

//this represents the time it takes to return after the final END_IO
int handle_loop(){
    return 20;
}