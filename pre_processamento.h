////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
//   Preprocessamento: Somente avalia as diretivas EQU e IF.  //
////////////////////////////////////////////////////////////////

#ifndef PRE_PROCESSAMENTO_HEADER
#define PRE_PROCESSAMENTO_HEADER

#include "functions.h"

// Realiza o pré processamento do arquivo
void pre_processamento(char const *source_file, char const *output_file);


void pre_processamento(char const *source_file, char const *output_file){
    char pre_output_file[ MAX_IDENTIFIER_WIDTH + 5 ];
    strcpy(pre_output_file, output_file);

    FILE *source_ptr; // Arquivo de entrada - source file pointer
    FILE *output_ptr; // Arquivo de saída - output file pointer
    FILE *temp_ptr; // Arquivo temporário.

    source_ptr = fopen(source_file, "r"); // Abre o arquivo de entrada em modo leitura.

    output_ptr = fopen(strcat(pre_output_file, ".pre"), "w"); // Cria o arquivo de saída com o nome dado pelo usuário. Será modificado posteriormente.

    temp_ptr = tmpfile();

    if ( source_ptr == NULL ){
        printf("\n Houve um erro ao abrir o arquivo %s !\n", source_file);
        exit(1);
    }

    if ( output_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo %s !\n", output_file);
        exit(1);
    }

    if ( temp_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo temporário! \n");
        exit(1);
    }

    else {
        while ( source_ptr != NULL ){


            //TODO: Rotina de pré-processamento.


        }
    }
    fclose (source_ptr);
    fclose (output_ptr);

}



#endif
