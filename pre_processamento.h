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

    token_t *token_list = NULL;

    int line_count = 0;

    strcpy(pre_output_file, output_file);

    FILE *source_ptr; // Arquivo de entrada - source file pointer
    FILE *output_ptr; // Arquivo de saída - output file pointer
    FILE *binary_ptr; // Arquivo intermediário - binary file pointer

    source_ptr = fopen(source_file, "r"); // Abre o arquivo de entrada em modo leitura.

    output_ptr = fopen(strcat(pre_output_file, ".pre"), "w"); // Cria o arquivo de saída com o nome dado pelo usuário.

    binary_ptr = fopen(strcat(pre_output_file, ".pre.tmp"), "wb"); // Cria o arquivo intermediário com o nome dado pelo usuário.


    if ( source_ptr == NULL ){
        printf("\n Houve um erro ao abrir o arquivo %s !\n", source_file);
        exit(1);
    }

    if ( output_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo %s !\n", output_file);
        exit(1);
    }

    if ( binary_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo temporário! \n");
        exit(1);
    }


    while ( feof(source_ptr) ){
        ++line_count;

        generate_line_tokens_list(source_ptr, token_list, line_count, -1);

        if ( token_list == NULL ) continue;

        if ( ( token_list->type == label ) \
          && ( token_list->next->type == directive ) \
          && !( strcmp(token_list->next->token_identifier, "EQU") ) \
        ){
            // insert_label_into_symbol_table();

            // if ( token_list->next->next->type != number ) erro();
            // if ( token_list->next->next->next != NULL ) erro();
        }

        else if ( ( token_list->type == directive ) \
             && ( token_list->next->type == symbol ) \
             && !( strcmp(token_list->token_identifier, "IF") ) \
        ){


        }

        else {
            // write_line_into_output();
            // save_list_into_file();
            erase_token_list(token_list);
        }



    }

    fclose (source_ptr);
    fclose (output_ptr);

}



#endif
