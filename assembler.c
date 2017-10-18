////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////

#include "functions.h"
#include "pre_processamento.h"

int main(int argc, char const *argv[]) {

    if ( valid_command(argc, argv) ){           // Teste de argumentos
        return 1;
    }

    if ( !(strcmp(argv[1], "-p")) ){       // Pré-processamento
        pre_processamento(argv[2], argv[3]);
    }

    else if ( !(strcmp(argv[1], "-m")) ) { // Expansão de macros
        pre_processamento(argv[2], argv[3]);
        // expansao_de_macros();   // FIXME
    }

    else {                                      // Montagem
        pre_processamento(argv[2], argv[3]);
        // expansao_de_macros();   // FIXME
        // montagem();             // FIXME
    }


    return 0;
}
