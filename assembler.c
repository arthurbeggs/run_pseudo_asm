////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////

#include "assembler.h"

int main(int argc, char const *argv[]) {

    if ( valid_command(argc, argv) ){           // Teste de argumentos
        return 1;
    }

    if ( !(strcmp(arguments[1], "-p")) ){       // Pré-processamento
        pre_processamento();    // FIXME
    }

    else if ( !(strcmp(arguments[1], "-m")) ) { // Expansão de macros
        pre_processamento();    // FIXME
        expansao_de_macros();   // FIXME
    }

    else {                                      // Montagem
        pre_processamento();    // FIXME
        expansao_de_macros();   // FIXME
        montagem();             // FIXME
    }


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
    else return 0;
}
