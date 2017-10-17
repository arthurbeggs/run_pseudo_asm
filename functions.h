////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////

#define MAX_LINE_WIDTH 500
#define MAX_IDENTIFIER_WIDTH 100

// Enumeração dos tipos de token existentes.
// Undefined é um token não avaliado, e invalid é um token inválido.
typedef enum { undefined = 0, label, instruction, directive, symbol, number, comma, plus, minus, invalid } token_type;


//TODO: Implementar como lista duplamente encadeada
typedef struct token_t{
    char token_identifier[ MAX_IDENTIFIER_WIDTH +1 ];
    token_type type;        // Tipo do token;
    int source_file_line;   // Linha do arquivo original;
    int output_file_byte;   // Posição de memoria no arquivo de saída;
    token_t *prev;          // Ponteiro para o token anterior;
    token_t *next;          // Ponteiro para o próximo token;
}token_t;


// Lê uma linha do arquivo de entrada e salva a linha no buffer fornecido.
// Retorna caso o arquivo tenha terminado.
void read_file_line(FILE *input_file, char *output_string);


// Lê o primeiro token de uma linha.
// Retorna a quantidade de caracteres do token (desconsiderando '\0').
int get_next_token(char *input_line, char *output_token);
