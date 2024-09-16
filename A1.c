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
    return 0;

}
