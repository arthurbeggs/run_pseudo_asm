////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
//       Arquivo que realiza a montagem de uma passagem.      //
////////////////////////////////////////////////////////////////

#ifndef MONTADOR_HEADER
#define MONTADOR_HEADER

#include "functions.h"


// Monta o código
void montagem(char const *source_file);


void montagem(char const *source_file){

    char temp_string[ MAX_IDENTIFIER_WIDTH + 5 ];
    token_t *token_list = NULL;

    FILE *source_ptr; // Ponteiro do arquivo de saída do pré processamento
    FILE *output_ptr; // Ponteiro do arquivo de saída do processamento da macro


    // Abre o arquivo com lista de tokens em modo leitura binária.
    strcpy(temp_string, source_file);
    strcat(temp_string, ".mcr.tmp");
    source_ptr = fopen(temp_string, "rb");
    if ( source_ptr == NULL ){
        printf("\n Houve um erro ao abrir o arquivo %s !\n", temp_string);
        exit(1);
    }

    // Cria o arquivo de saída em modo escrita.
    strcpy(temp_string, source_file);
    strcat(temp_string, ".o");
    output_ptr = fopen(temp_string, "w");
    if ( output_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo %s !\n", temp_string);
        exit(1);
    }


    while ( !( feof(source_ptr) ) ) {
        erase_token_list(&token_list);
        retrieve_token_list_from_file(&token_list, source_ptr);
        if ( feof(source_ptr) ) break;
        write_line_into_output(token_list, output_ptr);
    }

}



#endif
