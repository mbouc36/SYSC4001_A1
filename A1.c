#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    FILE  *file_ptr;

    file_ptr = fopen("trace.txt","r");

    char ch;

    if (NULL == file_ptr){
        printf("File can't open\n");
        return 0;

    }

    while ((ch = fgetc(file_ptr)) != EOF){
        printf("%c",ch);
    }
    fclose(file_ptr);
    

    //initial memory address, interrupt number, ISR address, duration of ISR in ms
    int vector_table[3][4] = {{0, 7, 14, 110},
                          {0, 12, 24, 250}, 
                          {0, 20, 40, 170},
                          {0, 22, 22, 328}};
                          
                          
    return 0;

}
