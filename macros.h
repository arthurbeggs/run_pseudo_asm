////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
//   Processamento de Macros: Somente avalia as diretivas     //
//               EQU e IF e substitue as macros.              //
////////////////////////////////////////////////////////////////

// Assumir que as macros vão sempre estar declaradas antes de serem \\
 chamadas e dentro da seção de texto. Assumir QUE NÃO TEM MACRO QUE \\
 CHAMA OUTRA MACRO. As macros NÃO precisam receber parâmetros (não  \\
 será feito teste de macro utilizando parâmetros de entrada).

#ifndef PROCESSAMENTO_MACRO_HEADER
#define PROCESSAMENTO_MACRO_HEADER

#include "functions.h"

//substitue as macros
void processa_macros(char const *output_file){

    //Passos dessa função:
    // 1 - Abre arquvo binario de saída do pre_processamento
    // 2 - Reorganiza o arquivo em lista (function)
    // 3 - Verifica se é Section Text, se não for, escreve direto\\
     no arquivo de saída. Se for, trata macros.
    // 4 - Na section text: Verifica se é macro ou não. Se for, guarda o nome na \\
    na MNT e o código na MDT.
    // 5 - Verifica se é chamada de macro ou definição de macro. Se definição, \\
    realiza passo 4. Se não, verifica se a macro está definida na MNT e \\
    substitue a linha pelo corpo da macro.

    char pre_output_file[ MAX_IDENTIFIER_WIDTH + 5 ];

    token_t *token_list = NULL;

    int line_count = 0;

    strcpy(macro_output_file, output_file);

    FILE *binary_ptr; // Arquivo de saída do pré processamento - output file pointer
    FILE *macro_processada_ptr; // Ponteiro do arquivo de saída do processamento da macro

    binary_ptr = fopen(strcat(macro_output_file, ".pre.tmp"), "r"); // Abre o arquivo de entrada em modo leitura.

    macro_processada_ptr = fopen(strcat(macro_output_file, ".mcr"), "w"); // Cria o arquivo de saída com o nome dado pelo usuário.

    if ( binary_ptr == NULL ){
        printf("\n Houve um erro ao abrir o arquivo %s temporário!\n", (strcat(macro_output_file, ".pre.tmp"));
        exit(1);
    }

    if ( macro_processada_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo %s !\n", (strcat(macro_output_file, ".mrc"));
        exit(1);
    }

while !(feof(binary_ptr) ){

    ++line_count;

    // Apaga os nós já existentes da lista de tokens.
    erase_token_list(&token_list);

    //lê uma linha do arquivo binario e transforma em lista;
    convert_line_binary_file_to_list(); //TODO;

    if ( ( token_list->type == label ) \
      && ( token_list->next->type == directive ) \
      && !( strcmp(token_list->next->token_identifier, "MACRO") ) \
    ) {
        //guarda label e linha da macro na mnt se ainda nao estiver. Caso esteja, mostra mensagem de erro.
        if

        //Lê nova linha


    // if (x == section text)
    //     SECTION_TEXT_FLAG = 1;



    fclose (output_ptr);
    fclose (macro_processada_ptr);
}

#endif
