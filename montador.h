////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
// Arquivo que finalmente realiza a montagem de uma passagem. //
////////////////////////////////////////////////////////////////

#ifndef MONTADOR_HEADER
#define MONTADOR_HEADER

#include "function.h"

typedef struct assemble_symble_table{
    char name_symble[ MAX_IDENTIFIER_WIDTH +1 ];
    int define;  // Diz se o simbolo já foi definido ou não. Comtem 0 se false e 1 se true;
    int value;   //endereço do símbolo
    token_t *list_of_use; //lista que contem os endereços em que os símbolos foram usados, para os simbolos ainda não definidos;
    struct assemble_symble_table *next;   // Ponteiro para a proxima linha da tabela;
}assemble_symble_table;


void montador_uma_passagem (char const *source_file, char const *output_file, char const *binary_ptr)


void montador_uma_passagem (char const *source_file, char const *output_file, char const *binary_ptr)

    char temp_string[ MAX_IDENTIFIER_WIDTH + 5 ];

    token_t *token_list = NULL;

    assemble_symble_table *name_symble = NULL;

    int line_count = 0, temp, status;

    strcpy(temp_string, output_file);

    FILE *source_ptr; // Arquivo de entrada - source file pointer
    FILE *output_ptr; // Arquivo de saída - output file pointer
    FILE *binary_ptr; // Arquivo intermediário - binary file pointer

    source_ptr = fopen(source_file, "r"); // Abre o arquivo de entrada em modo eitura.

    output_ptr = fopen(strcat(temp_string, ".o"), "w"); // Cria o arquivo de saída com o nome dado pelo usuário.

    binary_ptr = fopen(strcat(temp_string, ".tmp"), "wb"); // Cria o rquivo intermediário com o nome dado pelo usuário.

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

    while ( !(feof(source_ptr)) ){
        ++line_count;

        // Apaga os nós já existentes da lista de tokens;
        erase_token_list(&token_list);

        // Lê uma linha do arquivo binário temporário resultante do processamento de macros e transforma em lista;
        retrieve_token_list_from_file(*source_ptr)

        // Analisa o conteúdo do primeiro nó e escreve o operador corresponde no arquivo de saída, caso seja uma instrução, escreve o rótulo na tabela de símbolos. Preencher a tabela de simbolos deixando o lugar na tabela para os simbolos ainda nao definidos e formar a lista de endereços em que este deve ser substituido posteriormente.

        switch (token_type){
            case label:
                //salva na tabela de símbolos
                break;
            case directive:
                break;
            case instruction:
                switch(token_identifier){
                    case ADD:
                        write_in_file_object(1);
                        // Árvore derivativa para o ADD (ADD 2 || add N)
                        if (!( strcmp(token_list->token_identifier, "ADD") )\
                          && ((token_list->next->type == number)||(token_list->next->type == constante)) && token_list->next->next->next == NULL) {
                              //passar o endereço do argumento para o arquivo de saida
                        }
                        else{
                            printf("[ERRO SINTÁTICO] A%s\n", );
                        }

                        break;
                    case SUB:
                        write_in_file_object(2);
                        break;
                    case MULT:
                        write_in_file_object(3);
                        break;
                    case DIV:
                        write_in_file_object(4);
                        break;
                    case JMP:
                        write_in_file_object(5);
                        break;
                    case JMPN:
                        write_in_file_object(6);
                        break;
                    case JMPP:
                        write_in_file_object(7);
                        break;
                    case JMPZ:
                        write_in_file_object(8);
                        break;
                    case COPY:
                        write_in_file_object(9);
                        break;
                    case LOAD:
                        write_in_file_object(10);
                        break;
                    case STORE:
                        write_in_file_object(11);
                        break;
                    case INPUT:
                        write_in_file_object(12);
                        break;
                    case OUTPUT:
                        write_in_file_object(13);
                        break;
                    case STOP:
                        write_in_file_object(14);
                        break;
                    default:
                        //print error mensage
                        break;
                    }
            default:
                break;
                }

    // // Árvore derivativa para o ADD (ADD 2 || add N)
    // if (!( strcmp(token_list->token_identifier, "ADD") )\
    //   && ((token_list->next->type == number)||(token_list->next->type == constante))) {
    //         }
    //
    // // Árvore derivativa para o sub  (sub 2 || sub N)
    // if (!( strcmp(token_list->token_identifier, "SUB") )\
    //   && ((token_list->next->type == number)||(token_list->next->type == constante))) {
    //   }
    //
    // // Árvore derivativa para o MULT  (MULT 2 || MULT N)
    // if (!( strcmp(token_list->token_identifier, "MULT") )\
    //   && ((token_list->next->type == number)||(token_list->next->type == label))) {
    //     }
    //
    // // Árvore derivativa para o DIV  (DIV 2 || DIV N)
    // if (!( strcmp(token_list->token_identifier, "DIV") )\
    //   && ((token_list->next->type == number)||(token_list->next->type == label))) {
    //     }
    //
    // // Árvore derivativa para o JMP  ( JMP N)
    // if (!( strcmp(token_list->token_identifier, "JMP") )\
    //   && (token_list->next->type == label)) {
    //     }
    //
    // // Árvore derivativa para o JMPN  ( jmpn N)
    // if ((!( strcmp(token_list->token_identifier, "JMPN") ))\
    //   && (token_list->next->type == label)) {
    //     }
    //
    // // Árvore derivativa para o JMPP  ( JMPP N)
    // if ((!( strcmp(token_list->token_identifier, "JMPP") ))\
    //   && (token_list->next->type == label)) {
    //     }
    //
    // // Árvore derivativa para o JMPZ  ( JMPZ N)
    // if ((!( strcmp(token_list->token_identifier, "JMPZ") ))\
    //   && (token_list->next->type == label)) {
    //     }
    //
    // // Árvore derivativa para o JMPZ  ( JMPZ N)
    // if ((!( strcmp(token_list->token_identifier, "JMPZ") ))\
    //   && (token_list->next->type == label)) {
    //     }
    //
    // // Árvore derivativa para o LOAD  ( LOAD N)
    // if ((!( strcmp(token_list->token_identifier, "LOAD") ))\
    //   && (token_list->next->type == label)) {
    //     }
    //
    // // Árvore derivativa para o STORE ( STORE N)
    // if ((!( strcmp(token_list->token_identifier, "STORE") ))\
    //   && (token_list->next->type == label)) {
    //     }
    //
    // // Árvore derivativa para o OUTPUT  ( OUTPUT N)
    // if ((!( strcmp(token_list->token_identifier, "OUTPUT") ))\
    //   && (token_list->next->type == label)) {
    //     }
    //
    // // Árvore derivativa para o INPUT  ( INPUT N)
    // if ((!( strcmp(token_list->token_identifier, "INPUT") ))\
    //   && (token_list->next->type == label)) {
    //     }
    //
    // // Árvore derivativa para o COPY (COPY A, B)
    // if ((!( strcmp(token_list->token_identifier, "COPY") ))\
    //   && (token_list->next->type == label) && (token_list->next->next->type == label)) {
    //     }
    //
    // // ÁRVORE derivativa para STOP
    // if ((!( strcmp(token_list->token_identifier, "STOP") ))\
    //   && (token_list->next->token_identifier == "NULL")) {
    //     }
    //

    fclose (source_ptr);
    fclose (output_ptr);
    fclose (binary_ptr);

}

#endif
