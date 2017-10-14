#include "assembler.h"

int main(int argc, char const *argv[]) {

    valid_command(argc, argv);


    return 0;
}



int valid_command(int count, char const *arguments[]){
    char * temp;
    if ( \
        (count != 4) \
        || (   (strcmp(arguments[1], "-p")) \
            && (strcmp(arguments[1], "-m")) \
            && (strcmp(arguments[1], "-o")) ) \
        || ( (temp = strstr(arguments[2], ".asm")) == NULL) \
        || ( (*(temp+4)) != '\0') \
        || ( (temp = strstr(arguments[3], ".o")) == NULL) \
        || ( (*(temp+2)) != '\0') \
    ) {
        printf("%s", man_message);
        return 1;
    }
    else return 0;  // Bad arguments
}
