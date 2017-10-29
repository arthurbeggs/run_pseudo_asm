////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
//   Processamento de Macros: Somente substitui as macros.    //
////////////////////////////////////////////////////////////////

// Assumir que as macros vão sempre estar declaradas antes de serem  chamadas e dentro da seção de texto. Assumir QUE NÃO TEM MACRO QUE  CHAMA OUTRA MACRO. As macros NÃO precisam receber parâmetros (não   será feito teste de macro utilizando parâmetros de entrada).

#ifndef PROCESSA_MACRO_HEADER
#define PROCESSA_MACRO_HEADER

#include "functions.h"


// Substitui as macros
void processa_macros(char const *source_file);


void processa_macros(char const *source_file){

    //Passos dessa função:
    // 1 - Abre arquvo binario de saída do pre_processamento
    // 2 - Reorganiza o arquivo em lista (function)
    // 3 - Verifica se é Section Text, se não for, escreve direto no arquivo de saída. Se for, trata macros.
    // 4 - Na section text: Verifica se é macro ou não. Se for, guarda o nome na MNT e o código na MDT.
    // 5 - Verifica se é chamada de macro ou definição de macro. Se definição,  realiza passo 4. Se não, verifica se a macro está definida na MNT e     substitue a linha pelo corpo da macro.

    char temp_string[ MAX_IDENTIFIER_WIDTH + 5 ];

    // Identificam se o arquivo já chegou nas seções de dados ou texto.
    int inside_text_section, inside_data_section;

    inside_text_section = inside_data_section = 0;

    token_t *token_list = NULL;

    macro_name_table_t *macro_table = NULL;
    macro_name_table_t *temp = NULL;
    macro_def_table_t  *define_ptr = NULL;

    FILE *source_ptr; // Ponteiro do arquivo de saída do pré processamento
    FILE *binary_ptr; // Ponteiro para o arquivo intermediário.
    FILE *output_ptr; // Ponteiro do arquivo de saída do processamento da macro


    // Abre o arquivo com lista de tokens em modo leitura binária.
    strcpy(temp_string, source_file);
    strcat(temp_string, ".pre.tmp");
    source_ptr = fopen(temp_string, "rb");
    if ( source_ptr == NULL ){
        printf("\n Houve um erro ao abrir o arquivo %s !\n", temp_string);
        exit(1);
    }

    // Cria o arquivo de saída em modo escrita.
    strcpy(temp_string, source_file);
    strcat(temp_string, ".mcr");
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

    while ( !( feof(source_ptr) ) ) {

        temp = NULL;
        token_list = NULL;
        retrieve_token_list_from_file(&token_list, source_ptr);

        // Testa se a linha atual é uma declaração de section
        if (   ( token_list->type == directive ) \
            &&  ( token_list->next->type == directive ) \
            && !( strcmp(token_list->token_id, "SECTION") ) \
        ) {

            // Seção DATA
            if ( !( strcmp(token_list->next->token_id, "DATA") ) ) {
                inside_data_section = 1;
                inside_text_section = 0;
            }

            // Seção TEXT
            else if ( !( strcmp(token_list->next->token_id, "TEXT") ) ) {
                inside_text_section = 1;
                inside_data_section = 0;
            }

            // Seção inválida
            else {
                inside_text_section = 0;
                inside_data_section = 0;
            }
        }

        // Lê definições de macros
        else if  (  ( inside_text_section ) \
            && ( token_list->type == label ) \
            && ( token_list->next->type == directive ) \
            && ( !( strcmp(token_list->next->token_id, "MACRO") ) )
        ){

            if ( insert_label_into_macro_name_table( \
                    &macro_table, \
                    token_list->token_id, \
                    &temp ) \
            ) {
                printf( MACRO_REDEFINED, token_list->source_file_line );

                // Apaga macro sem colocá-la na tabela de definições
                while ( !!( strcmp(token_list->token_id, "ENDMACRO") ) ){
                    erase_token_list(&token_list);
                    retrieve_token_list_from_file(&token_list, source_ptr);

                    if ( feof(source_ptr) ){
                        printf( EOF_REACHED_BEFORE_END, temp->symbol );
                        exit(1);
                    }

                    // Sem testes extras devido às definições da especificação.
                }
                erase_token_list(&token_list);
                goto case_break;
            }

            while ( !!( strcmp(token_list->token_id, "ENDMACRO") ) ){
                token_list = NULL;
                retrieve_token_list_from_file(&token_list, source_ptr);

                if ((!( strcmp(token_list->token_id, "ENDMACRO")) )) {
                    erase_token_list(&token_list);
                    break;
                }

                if ( feof(source_ptr) ){
                    printf( EOF_REACHED_BEFORE_END, temp->symbol );
                    exit(1);
                }

                insert_line_into_macro_def_table( &temp, &token_list );
            }
        }

        // Substitui macro
        else if ( token_list->type == symbol ) {
            retrieve_macro_from_table( &macro_table, token_list->token_id, &temp );
            if ( temp != NULL ){
                define_ptr = temp->definition;

                // Percorre os nós da MDT e grava os arquivos.
                while ( define_ptr ){
                    write_line_into_output(define_ptr->macro_line, output_ptr);
                    save_list_into_file(define_ptr->macro_line, binary_ptr);
                    define_ptr = define_ptr->next;
                }
                continue; // Passa para a próxima iteração do loop
            }
        }

        case_break:
        if ( feof(source_ptr) ) break;
        // Escreve a lista no arquivo .mcr e salva a lista de tokens no arquivo binário.
        write_line_into_output(token_list, output_ptr);
        save_list_into_file(token_list, binary_ptr);
    }

    erase_macro_table(&macro_table);

    fclose (source_ptr);
    fclose (output_ptr);
    fclose (binary_ptr);

}

#endif
