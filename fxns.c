//switches user modes (1 ms)
int switch_user_modes(){
    return 1;
}

//saves and restores context (10-30 ms random)
int save_restore_context(){
    int min = 10;
    int max = 30;

    // Generate a random number between 10 and 30
    int randomInt = rand() % (max - min + 1) + min;
    return randomInt;
}

// calculates where in memory the ISR starts (1ms)
int get_ISR_start_address(){
    return 1;
}

//get the address if the ISR from the vector table (1 ms)
int get_ISR_address_from_vector_table(){
    return 1;
}

//execute the instructions for the ISR (20-40ms)
int execute_ISR(){
    int min = 20;
    int max = 40;

    // Generate a random number between 10 and 30
    int randomInt = rand() % (max - min + 1) + min;
    return randomInt;
}

//Return the value from the interrupt subroutine ( 1ms)
int IRET(){
    return 1;
}
