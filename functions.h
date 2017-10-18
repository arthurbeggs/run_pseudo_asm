////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////

// Testa se o cabeçalho já foi incluso. Se não, o inclui.
#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER


// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Definições de macros
#define MAX_LINE_WIDTH 500
#define MAX_IDENTIFIER_WIDTH 100

#define MAN_MESSAGE "\
*************************************************************\n\
*********         Montador Pseudo-Assembly          *********\n\
*************************************************************\n\n\
                    Argumentos inválidos!\n\n\
  Modo de uso:\n\
   > %s -p <source_file> <output_file>\n\
     Pré-processamento do código.\n\
       - <source_file> deve ter extensão .asm;\n\
       - <output_file> deve ter extensão .o;\n\
       - <output_file> será concatenado com a \
extensão .pre .\n\n\
   > %s -m <source_file> <output_file>\n\
     Processamento de macros.\n\
       - <source_file> deve ter extensão .asm;\n\
       - <output_file> deve ter extensão .o;\n\
       - <output_file> será concatenado com a \
extensão .mcr .\n\n\
   > %s -o <source_file> <output_file>\n\
     Realiza a montagem do código.\n\
       - <source_file> deve ter extensão .asm;\n\
       - <output_file> deve ter extensão .o . \n\n\
*************************************************************\n"


// Definições de tipos

// Enumeração dos tipos de token existentes.
// Undefined é um token não avaliado, e invalid é um token inválido.
typedef enum { undefined = 0, label, instruction, directive, symbol, number, comma, plus, minus, invalid } token_type;


typedef struct token_t{
    char token_identifier[ MAX_IDENTIFIER_WIDTH +1 ];
    token_type type;        // Tipo do token;
    int source_file_line;   // Linha do arquivo original;
    int output_file_byte;   // Posição de memoria no arquivo de saída;
    struct token_t *prev;          // Ponteiro para o token anterior;
    struct token_t *next;          // Ponteiro para o próximo token;
}token_t;



// Protótipos de funções


// Avalia se os argumentos passados ao programa estão corretos.
int valid_command(int, char const **);


// Lê uma linha do arquivo de entrada e salva a linha no buffer fornecido.
// Retorna caso o arquivo tenha terminado.
void read_file_line(FILE *source_file, char *output_string);


// Lê o primeiro token de uma linha.
// Retorna a quantidade de caracteres do token (desconsiderando '\0').
int get_next_token(char *input_line, char *output_token);


// Extrai os tokens de uma linha.
void generate_line_tokens_list(FILE *input_file, token_t *token_list, int line_count, int byte_count);


// Salva no nó o tipo do token
void define_token_type(token_t *node);


// Testa se o token é um símbolo
int is_symbol(char *id);


// Testa se o token é um número
int is_number(char *id);


// Testa se o token é igual ao caracter fornecido
int is_char(char *id, const char *character);


// Testa se o token é uma diretiva
int is_directive(char *id);


// Testa se o token é uma istrução
int is_instruction(char *id);


// Converte as letras minúsculas para maiúsculas.
void convert_string_to_all_caps(char *id);


// Insere novo nó na lista;
// Retorna um ponteiro para o elemento recém-adicionado;
token_t * insert_node_at_list_end(token_t **token_list, char *retrieved_token_id, int line_count, int byte_count);


// Desaloca lista
void remove_token_list(token_t *token_list);



// #endif precisa ser a última linha
#endif
