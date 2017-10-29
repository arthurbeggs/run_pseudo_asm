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

    // int word_count = 0;

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

        if ( token_list->type == label ) {
            if ( token_list->next->type == directive ) {
                if ( !(strcmp(token_list->next->token_id, "SPACE") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "CONST") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "BEGIN") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "EXTERN") ) ) {

                }

                // Erro
                else {

                }


            }

            else if ( token_list->next->type == instruction ) {
                //TODO: Passar para função depois de definir argumentos
                if ( !(strcmp(token_list->next->token_id, "ADD") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "SUB") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "MULT") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "DIV") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "JMP") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "JMPN") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "JMPP") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "JMPZ") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "COPY") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "LOAD") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "STORE") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "INPUT") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "OUTPUT") ) ) {

                }

                else if ( !(strcmp(token_list->next->token_id, "STOP") ) ) {

                }

            }

            // Erro
            else {
                printf( TIPO_DE_ARGUMENTO_INVALIDO, token_list->source_file_line );
                continue;
            }

        }

        else if ( token_list->type == directive ) {
            if ( !(strcmp(token_list->next->token_id, "SECTION") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "END") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "PUBLIC") ) ) {

            }

            // Erro
            else {
                printf( TIPO_DE_ARGUMENTO_INVALIDO, token_list->source_file_line );
                continue;
            }

        }

        else if ( token_list->type == instruction ) {
            //TODO: Passar para função depois de definir argumentos
            if ( !(strcmp(token_list->next->token_id, "ADD") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "SUB") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "MULT") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "DIV") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "JMP") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "JMPN") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "JMPP") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "JMPZ") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "COPY") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "LOAD") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "STORE") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "INPUT") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "OUTPUT") ) ) {

            }

            else if ( !(strcmp(token_list->next->token_id, "STOP") ) ) {

            }
        }

        // Fim do arquivo
        else if ( feof(source_ptr) ) break;

        // Erro
        else {
            printf( INVALID_TOKEN_AT_LINE_START, token_list->token_id );
            continue;
        }


    }

}



#endif
