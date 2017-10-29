////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
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
void pre_processamento(char const *source_file, int with_modules);


void pre_processamento(char const *source_file, int with_modules){

    char temp_string[ MAX_IDENTIFIER_WIDTH + 5 ];

    token_t *token_list = NULL;
    token_t *list_crawler = NULL;

    symbol_table_t *symbol_table = NULL;

    int line_count = 0, temp, status;


    FILE *source_ptr; // Arquivo de entrada - source file pointer
    FILE *output_ptr; // Arquivo de saída - output file pointer
    FILE *binary_ptr; // Arquivo intermediário - binary file pointer

    // Abre o arquivo de entrada em modo leitura.
    strcpy(temp_string, source_file);
    strcat(temp_string, ".asm");
    source_ptr = fopen(temp_string, "r");
    if ( source_ptr == NULL ){
        printf("\n Houve um erro ao abrir o arquivo %s !\n", temp_string);
        exit(1);
    }

    // Cria o arquivo de saída em modo escrita.
    strcpy(temp_string, source_file);
    strcat(temp_string, ".pre");
    output_ptr = fopen(temp_string, "w");
    if ( output_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo %s !\n", temp_string);
        exit(1);
    }

    // Cria o arquivo intermediário em modo de escrita binária.
    binary_ptr = fopen(strcat(temp_string, ".tmp"), "wb");
    if ( binary_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo temporário! \n");
        exit(1);
    }


    while ( !(feof(source_ptr)) ){
        ++line_count;

        // Apaga os nós já existentes da lista de tokens.
        erase_token_list(&token_list);

        // Lê uma nova linha do arquivo e a separa em uma lista de tokens
        generate_line_tokens_list(source_ptr, &token_list, &line_count, -1);

        // Se a linha estiver vazia, lê a próxima linha.
        if ( token_list == NULL ) continue;


        // Testa se o programa não tem módulos, mas tem diretiva BEGIN ou END
        if ( !(with_modules) ) {
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
                    erase_symbol_table(symbol_table);
                    fclose (source_ptr);
                    fclose (output_ptr);
                    fclose (binary_ptr);
                    exit(1);
                }
                list_crawler = list_crawler->next;
            }
        }


        // Testa se a linha tem uma diretiva EQU na posição esperada (2º token, antecedido de um label).
        if ( ( token_list->type == label ) \
          && ( token_list->next != NULL ) \
          && ( token_list->next->type == directive ) \
          && !( strcmp(token_list->next->token_id, "EQU") ) \
        ) {
            // Se o 3º token da linha não for um número ou um sinal seguido de número, lança a mensagem de erro e passa para a leitura da próxima linha, ignorando a atual.
            if ( ( token_list->next->next->type != number ) \
                && !( ( ( token_list->next->next->type == plus ) \
                     || ( token_list->next->next->type == minus )  )  \
                     && ( token_list->next->next->next->type == number ) ) \
            ) {
                printf( EQU_INVALID_ARGUMENT, token_list->next->source_file_line );
                continue;
            }

            // Se a linha possuir mais tokens que o esperado, lança a mensagem de erro, ignora os tokens excedentes e continua a análise.
            if  (   (       ( token_list->next->next->type == number ) \
                    &&      ( token_list->next->next->next != NULL ) \
                    ) \
                ||  (   (   ( token_list->next->next->type == plus ) \
                        ||  ( token_list->next->next->type == minus ) \
                        )\
                    &&  (   ( token_list->next->next->next->type != number ) \
                        ||  ( token_list->next->next->next->next != NULL ) \
                    ) \
                )\
            ) {
                printf( EQU_TOO_MUCH_ARGUMENTS, token_list->next->source_file_line );
            }

            strcpy(temp_string, token_list->next->next->token_id);

            // Adiciona sinal ao valor do símbolo, caso exista
            if ( ( token_list->next->next->type != number ) ) {
                strcat(temp_string, token_list->next->next->next->token_id);
            }

            // Se o símbolo já tiver sido inserido na tabela de símbolos, seu valor é substituído pelo mais recente, uma mensagem de erro é lançada para indicar a redefinição de símbolos e passa para a leitura da próxima linha.
            if ( insert_label_into_symbol_table( \
                    &symbol_table, \
                    token_list->token_id, \
                    convert_string_to_int( temp_string ) ) \
            ) { printf( SYMBOL_REDEFINED, token_list->source_file_line ); }
            continue;
        }

        // Testa se a linha tem uma diretiva IF na posição esperada (1º token, sucedido de um símbolo).
        else if ( ( token_list->type == directive ) \
             && ( token_list->next != NULL ) \
             && ( token_list->next->type == symbol ) \
             && !( strcmp(token_list->token_id, "IF") ) \
        ){

            // Recupera símbolo da tabela.
            status = retrieve_symbol_from_table( \
                        symbol_table, \
                        token_list->next->token_id, \
                        &temp);

            // Se o símbolo não existir na tabela, lança mensagem de erro e apaga a linha atual e a próxima.
            if ( status == 0 ) {     // Símbolo não definido
                printf( SYMBOL_NOT_DECLARED, token_list->source_file_line );

                // Linha atual e a próxima são apagadas
                erase_token_list(&token_list);
                ++line_count;
                generate_line_tokens_list(source_ptr, &token_list, &line_count, -1);
                // Lista será apagada e line_count incrementado novamente na próxima iteração.
            }

            // Se o EQU apontado pelo símbolo for 0, apaga a linha seguinte.
            else if ( temp < 1 ) {     //Símbolo == 0
                // Linha atual e a próxima são apagadas
                erase_token_list(&token_list);
                ++line_count;
                generate_line_tokens_list(source_ptr, &token_list, &line_count, -1);
                // Lista será apagada e line_count incrementado novamente na próxima iteração.
            }
            // A linha será gravada no arquivo na próxima iteração.
        }

        // Escreve a linha atual no arquivo .pre, salva a lista de tokens no arquivo binário.
        else {
            replace_equ_defined_symbols(token_list, symbol_table);
            write_line_into_output(token_list, output_ptr);
            save_list_into_file(token_list, binary_ptr);
        }

    }

    erase_symbol_table(symbol_table);

    fclose (source_ptr);
    fclose (output_ptr);
    fclose (binary_ptr);

}



#endif
