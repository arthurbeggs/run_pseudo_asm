////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////

#include "functions.h"
#include "pre_processamento.h"
#include "processa_macros.h"

int main(int argc, char const *argv[]) {

    // Guarda nome do arquivo temporário para ser possível excluí-lo.
    char temp[ MAX_IDENTIFIER_WIDTH + 10 ];

    if ( valid_command(argc, argv) ){           // Teste de argumentos
        return 1;
    }

    if ( !(strcmp(argv[1], "-p")) ){       // Pré-processamento
        pre_processamento(argv[2], argv[3]);

        // // Apaga arquivo *.pre.tmp
        // strcpy(temp, argv[3]);
        // remove(strcat(temp, ".pre.tmp"));
    }

    else if ( !(strcmp(argv[1], "-m")) ) { // Expansão de macros
        pre_processamento(argv[2], argv[3]);
        // processa_macros(argv[3]);
        printf("\nExpansão de macros não funcionando :c \n");
        printf("O programa será finalizado.\n\n");

        // Apaga arquivo *.pre.tmp
        strcpy(temp, argv[3]);
        remove(strcat(temp, ".pre.tmp"));

        exit(1);

        // // Apaga arquivo *.mnt.tmp
        // strcpy(temp, argv[3]);
        // remove(strcat(temp, ".mcr.tmp"));
    }

    else {                                      // Montagem
        pre_processamento(argv[2], argv[3]);
        // processa_macros(argv[3]);
        printf("\nExpansão de macros não funcionando :c \n");
        printf("\nMontagem não implementada :C \n");
        printf("O programa será finalizado.\n\n");
        // montagem();             // FIXME

        // Apaga arquivo *.pre.tmp
        strcpy(temp, argv[3]);
        remove(strcat(temp, ".pre.tmp"));

        // // Apaga arquivo *.mnt.tmp
        // strcpy(temp, argv[3]);
        // remove(strcat(temp, ".mcr.tmp"));

        exit(1);
    }


    return 0;
}
