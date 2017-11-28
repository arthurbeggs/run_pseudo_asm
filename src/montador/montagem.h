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
// Se modularized == 1, o arquivo deve conter as diretivas BEGIN e END. Se modularized == 0 o arquivo não deve conter as diretivas BEGIN e END.
void montagem(char const *source_file, int modularized);


void montagem(char const *source_file, int modularized){

    char temp_string[ MAX_IDENTIFIER_WIDTH + 5 ];
    token_t *token_list                     = NULL;
    token_t *list_crawler                   = NULL;
    assembler_symbol_table_t *symbol_table  = NULL;
    assembler_symbol_table_t *table_ptr     = NULL;


    int word_count = 0;
    int value;
    int counter;
    const int zero = 0;

    FILE *source_ptr; // Ponteiro do arquivo de saída do processamento da macro
    FILE *output_ptr; // Ponteiro do arquivo de saída do montador
    FILE *binary_ptr; // Ponteiro do arquivo binário temporário
    //TODO: Fazer a merda do mapa de bits


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

    // Cria o arquivo intermediário em modo de leitura/escrita binária.
    binary_ptr = fopen(strcat(temp_string, ".tmp"), "wb+");
    if ( binary_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo temporário! \n");
        exit(1);
    }


    while ( !( feof(source_ptr) ) ) {
        erase_token_list(&token_list);
        retrieve_token_list_from_file(&token_list, source_ptr);

        if ( feof(source_ptr) ) break;

        // Testa se o programa não tem módulos, mas tem diretiva BEGIN ou END
        if ( !(modularized) ) {
            list_crawler = token_list;
            while ( list_crawler != NULL ) {
                if ( \
                        (  list_crawler->type == directive ) \
                    &&  (  !( strcmp(list_crawler->token_id, "BEGIN")) \
                        || !( strcmp(list_crawler->token_id, "END") ) \
                    ) \
                ) {
                    // Se o arquivo for standalone, mas possuir diretivas BEGIN ou END, exibe mensagem de erro, limpa a memória e encerra o programa com erro.
                    printf( STANDALONE_AS_MODULE_ERR, source_file );
                    erase_token_list(&token_list);
                    // TODO: Apagar tabela de símbolos
                    fclose (source_ptr);
                    fclose (output_ptr);
                    fclose (binary_ptr);
                    exit(1);
                }
                list_crawler = list_crawler->next;
            }
        }


        if ( token_list->type == label ) {
            if ( token_list->next->type == directive ) {
                if ( !(strcmp(token_list->next->token_id, "SPACE") ) ) {
                    table_ptr = define_entry_on_symbol_table( &symbol_table, token_list->token_id,  word_count );
                    save_defined_value_into_file( table_ptr->address, binary_ptr, word_count );

                    // Adicionar espaços em branco no arquivo
                    if ( token_list->next->next != NULL ){
                        value = convert_token_to_int(token_list->next->next->token_id);
                    }
                    else value = 1;
                    for (counter = 0; (counter < value) ; counter++){
                        fwrite( &zero, sizeof(int), 1, binary_ptr);
                        word_count++;
                    }
                }

                else if ( !(strcmp(token_list->next->token_id, "CONST") ) ) {
                    table_ptr = define_entry_on_symbol_table( &symbol_table, token_list->token_id,  word_count );
                    save_defined_value_into_file( table_ptr->address, binary_ptr, word_count );

                    value = convert_token_to_int(token_list->next->next->token_id);
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "BEGIN") ) ) {
                    table_ptr = define_entry_on_symbol_table( &symbol_table, token_list->token_id,  word_count );
                    save_defined_value_into_file( table_ptr->address, binary_ptr, word_count );
                    // DEBUG: Talvez BEGIN precise indicar a posição inicial do arquivo.
                }

                else if ( !(strcmp(token_list->next->token_id, "EXTERN") ) ) {
                    table_ptr = define_entry_on_symbol_table( &symbol_table, token_list->token_id,  0 );
                    save_defined_value_into_file( table_ptr->address, binary_ptr, 0 );
                    table_ptr->extern_symbol = 1;
                }

                // Erro
                else {
                    printf( TIPO_DE_ARGUMENTO_INVALIDO, token_list->source_file_line );
                    continue;
                }


            }

            else if ( token_list->next->type == instruction ) {
                table_ptr = define_entry_on_symbol_table( &symbol_table, token_list->token_id,  word_count );
                save_defined_value_into_file( table_ptr->address, binary_ptr, word_count );


                if ( !(strcmp(token_list->next->token_id, "ADD") ) ) {
                    value = 1;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "SUB") ) ) {
                    value = 2;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "MULT") ) ) {
                    value = 3;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "DIV") ) ) {
                    value = 4;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "JMP") ) ) {
                    value = 5;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "JMPN") ) ) {
                    value = 6;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "JMPP") ) ) {
                    value = 7;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "JMPZ") ) ) {
                    value = 8;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "COPY") ) ) {
                    value = 9;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, (find_token_by_type(token_list, comma))->next->token_id, word_count );
                    value += get_increment_value( (find_token_by_type(token_list, comma))->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "LOAD") ) ) {
                    value = 10;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "STORE") ) ) {
                    value = 11;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "INPUT") ) ) {
                    value = 12;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "OUTPUT") ) ) {
                    value = 13;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                    value = check_symbol_table( &symbol_table, token_list->next->next->token_id, word_count );
                    value += get_increment_value( token_list->next->next->next );

                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;
                }

                else if ( !(strcmp(token_list->next->token_id, "STOP") ) ) {
                    value = 14;
                    fwrite( &value, sizeof(int), 1, binary_ptr);

                    word_count++;

                }
            }

            // Erro
            else {
                printf( TIPO_DE_ARGUMENTO_INVALIDO, token_list->source_file_line );
                continue;
            }

        }

        else if ( token_list->type == directive ) {
            if ( !(strcmp(token_list->token_id, "SECTION") ) ) {

            }

            else if ( !(strcmp(token_list->token_id, "END") ) ) {

            }

            else if ( !(strcmp(token_list->token_id, "PUBLIC") ) ) {

            }

            // Erro
            else {
                printf( TIPO_DE_ARGUMENTO_INVALIDO, token_list->source_file_line );
                continue;
            }

        }

        else if ( token_list->type == instruction ) {
            if ( !(strcmp(token_list->token_id, "ADD") ) ) {
                value = 1;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "SUB") ) ) {
                value = 2;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "MULT") ) ) {
                value = 3;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "DIV") ) ) {
                value = 4;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "JMP") ) ) {
                value = 5;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "JMPN") ) ) {
                value = 6;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "JMPP") ) ) {
                value = 7;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "JMPZ") ) ) {
                value = 8;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "COPY") ) ) {
                value = 9;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, (find_token_by_type(token_list, comma))->next->token_id, word_count );
                value += get_increment_value( (find_token_by_type(token_list, comma))->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "LOAD") ) ) {
                value = 10;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "STORE") ) ) {
                value = 11;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "INPUT") ) ) {
                value = 12;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "OUTPUT") ) ) {
                value = 13;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

                value = check_symbol_table( &symbol_table, token_list->next->token_id, word_count );
                value += get_increment_value( token_list->next->next );

                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;
            }

            else if ( !(strcmp(token_list->token_id, "STOP") ) ) {
                value = 14;
                fwrite( &value, sizeof(int), 1, binary_ptr);

                word_count++;

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

    parse_bin_file_to_text(output_ptr, binary_ptr);


    erase_token_list(&token_list);
    // TODO: Apagar tabela de símbolos;
    fclose (source_ptr);
    fclose (output_ptr);
    fclose (binary_ptr);

}



#endif
