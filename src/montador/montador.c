////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
//                          Montador                          //
////////////////////////////////////////////////////////////////

#include "functions.h"
#include "pre_processamento.h"
#include "processa_macros.h"
#include "montagem.h"


int main(int argc, char const *argv[]) {

    // Guarda nome do arquivo temporário para ser possível excluí-lo.
    char temp[ MAX_IDENTIFIER_WIDTH + 10 ];
    char *str_pointer;

    int count;

    if ( !(valid_command(argc, argv)) ){        // Teste de argumentos
        return 1;
    }

    for ( count = 1 ; count < argc ; count++ ) {

        // Copia o nome do arquivo para temp e retira a extensão ".asm"
        strcpy(temp, argv[count]);
        str_pointer = strstr(temp, ".asm");
        *str_pointer = '\0';


        pre_processamento(temp);
        processa_macros(temp);
        montagem(temp, ( (int) argc > 2 ? 1 : 0 ));


        // Apaga arquivo *.pre.tmp
        remove(strcat(temp, ".pre.tmp"));

        // Apaga arquivo *.mcr.tmp
        strcpy(temp, argv[count]);
        str_pointer = strstr(temp, ".asm");
        *str_pointer = '\0';
        remove(strcat(temp, ".mcr.tmp"));

        // // Apaga arquivo *.o.tmp
        // strcpy(temp, argv[count]);
        // str_pointer = strstr(temp, ".asm");
        // *str_pointer = '\0';
        // remove(strcat(temp, ".o.tmp"));
    }




    return 0;
}
