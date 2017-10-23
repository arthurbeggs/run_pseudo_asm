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

#include "error_messages.h"


// Definições de macros
#define MAX_LINE_WIDTH 500
#define MAX_IDENTIFIER_WIDTH 100


// Definições de tipos

// Enumeração dos tipos de token existentes.
// Undefined é um token não avaliado, e invalid é um token inválido.
typedef enum { undefined = 0, label, instruction, directive, symbol, number, comma, plus, minus, invalid } token_type;


typedef struct token_t{
    char token_identifier[ MAX_IDENTIFIER_WIDTH +1 ];
    token_type type;        // Tipo do token;
    int source_file_line;   // Linha do arquivo original;
    int output_file_byte;   // Posição de memoria no arquivo de saída;
    struct token_t *prev;   // Ponteiro para o token anterior;
    struct token_t *next;   // Ponteiro para o próximo token;
}token_t;


typedef struct symbol_table_t{
    char symbol[ MAX_IDENTIFIER_WIDTH +1 ];
    int  value;
    struct symbol_table_t *next;
}symbol_table_t;

typedef struct macro_name_table{
    char name[ MAX_IDENTIFIER_WIDTH +1 ]; //nome da macro (label da macro)
    int source_file_line;   // Linha do arquivo original;
    int mdt_file_line;   // linha na tabela de definicoes mdt;
    struct macro_name_table *next;   // Ponteiro para a proxima linha da mnt;
}macro_name_table;

typedef struct macro_definition_table{
    int mdt_file_line;   // linha da tabela mdt;
    token_t *definition_of_macro; //lista que contem a definição da macro;
    struct macro_definition_table *next;   // Ponteiro para a proxima linha da mnt;
}macro_definition_table;


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
void generate_line_tokens_list(FILE *input_file, token_t **token_list, int *line_count, int byte_count);


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
void erase_token_list(token_t **token_list);


// Converte string para inteiro.
int convert_string_to_int(char *id);


// Insere novo nó na tabela. Se o símbolo já existir, sobrescreve seu valor
// Retorna 0 em caso de sucesso e 1 se o símbolo já existir na tabela.
int insert_label_into_symbol_table(symbol_table_t **symbol_table, char *id, int value);


// Desaloca tabela de símbolos
void erase_symbol_table(symbol_table_t *symbol_table);


// Procura símbolo na tabela.
// Retorna 0 caso o símbolo não tenha sido declarado. Senão, retorna 1.
int retrieve_symbol_from_table(symbol_table_t *symbol_table, char *id, int *value);


// Escreve linha no arquivo de saída.
void write_line_into_output(token_t *token_list, FILE *output_ptr);


// Salva lista em um arquivo binário
void save_list_into_file(token_t *token_list, FILE *binary_ptr);


// Troca símbolos já definidos por sua definição
void swap_equ_defined_symbols(token_t *token_list, symbol_table_t *symbol_table);




// Implementações

// Avalia se os argumentos passados ao programa estão corretos.
int valid_command(int count, char const *arguments[]){
    char const *temp;
    if ( \
        (count != 4) \
        || (   (strcmp(arguments[1], "-p")) \
            && (strcmp(arguments[1], "-m")) \
            && (strcmp(arguments[1], "-o")) ) \
        || ( (temp = strstr(arguments[2], ".asm")) == NULL) \
        || ( (*(temp+4)) != '\0') \
        || ( (temp = strstr(arguments[3], ".o")) == NULL) \
        || ( (*(temp+2)) != '\0') \
    ) {
        printf( MAN_MESSAGE, arguments[0], arguments[0], arguments[0] );
        return 1;
    }
    else return 0;
}


// Lê uma linha do arquivo de entrada e salva a linha no buffer fornecido.
// Retorna caso o arquivo tenha terminado.
void read_file_line(FILE *source_file, char *output_string){
    // Comportamento do scanset definido:
    // " " ignora espaços e tabs no início da linha;
    // %[^;\r\n] lê o restante da linha (máximo de 500 caracteres), para ao encontrar a primeira ocorrência de um comentário (;) ou um carriage return(\r) ou um line feed (\n) e salva a string lida em output_string;
    // %*[^\r\n] lê o restante da linha (comentário ou nada), para ao encontrar a primeira ocorrência de um carriage return(\r) ou um line feed (\n) e descarta a string lida;
    // %*[\r\n] lê o identificador de final de linha e o descarta. Funciona para identificador LF, CR e CRLF;
    //NOTE: Se o tamanho da macro MAX_LINE_WIDTH for alterado (!= 500), é necessário alterar o tamanho máximo do 2º parâmetro do scanset.

    // fscanf(source_file, " %500[^;\r\n]%*[^\r\n]%*[\r\n]", output_string);
    // fscanf(source_file, " %[^;\r\n]%*[^\r\n]%*[\r\n]", output_string);
    fscanf(source_file, " %500[^;\r\n]", output_string);
    fscanf(source_file, "%*[^\r\n]");
    fscanf(source_file, "%*[\r\n]");
}


// Lê o primeiro token de uma linha.
// Retorna a quantidade de caracteres do token (desconsiderando '\0').
int get_next_token(char *input_line, char *output_token){
    char *temp;

    *output_token = '\0';

    // Comportamento do scanset definido:
    // %*[ \t] ignora espaços e tabs que antecedem o token;
    // %[^ \t] lê o restante da linha (máximo de 100 caracteres), para ao encontrar a primeira ocorrência de um espaço ou tab e salva a string lida em output_token (não separa tokens ",", "+" e "-" quando emendados a outros tokens);
    //NOTE: Se o tamanho da macro MAX_IDENTIFIER_WIDTH for alterado (!= 500), é necessário alterar o tamanho máximo do 2º parâmetro do scanset.
    sscanf(input_line, " %100[^\t ]", output_token);

    // Testa se o token possui uma vírgula e a separa caso precise
    if ( ( temp = strstr(output_token, ",") ) ){
        // Se a posição da vírgula estiver em output_token[0], "apaga" o resto do token.
        if (temp == output_token) *(temp+1) = '\0';
        // Senão, "apaga" o resto do token, inclusive a vírgula.
        else *temp = '\0';
    }

    // Testa se o token possui um + e o separa caso precise
    else if ( ( temp = strstr(output_token, "+") ) ){
        // Se a posição do "+" estiver em output_token[0], "apaga" o resto do token.
        if (temp == output_token) *(temp+1) = '\0';
        // Senão, "apaga" o resto do token, inclusive o "+".
        else *temp = '\0';
    }

    // Testa se o token possui um - e o separa caso precise
    else if ( ( temp = strstr(output_token, "-") ) ){
        // Se a posição do "-" estiver em output_token[0], "apaga" o resto do token.
        if (temp == output_token) *(temp+1) = '\0';
        // Senão, "apaga" o resto do token, inclusive o "-".
        else *temp = '\0';
    }

    // Retorna a quantidade de caracteres de output_token
    if ( *output_token != '\0' ) return ( strlen(output_token) );
    else return 0;
}


// Extrai os tokens de uma linha.
void generate_line_tokens_list(FILE *source_file, token_t **token_list, int *line_count, int byte_count){

    // Linha recuperada do arquivo.
    char retrieved_line[ MAX_LINE_WIDTH + 1 ];
    // Ponteiro para a linha recuperada.
    char *line_ptr;

    // Token recuperado da linha.
    char retrieved_token_id[ MAX_IDENTIFIER_WIDTH + 1];
    // Tamanho do token recuperado.
    int  retrieved_token_length;

    // Ponteiro para o último nó criado da lista de tokens.
    token_t *last_created_node;

    retrieved_token_length = 0;
    line_ptr = retrieved_line;
    last_created_node = NULL;
    *(retrieved_line) = '\0';
    *(retrieved_token_id) = '\0';


    read_file_line(source_file, retrieved_line);

    retrieved_token_length = (int) get_next_token(line_ptr, retrieved_token_id);

    while ( retrieved_token_length ) {


        last_created_node = insert_node_at_list_end(token_list, retrieved_token_id, *line_count, byte_count);


        // Ponteiro da linha aponta para o primeiro caracter da linha após o último caracter do token recuperado.
        line_ptr = strstr(line_ptr, retrieved_token_id) + retrieved_token_length;

        // A conversão só pode ser feita após o incremento de line_ptr.
        convert_string_to_all_caps(last_created_node->token_identifier);

        define_token_type(last_created_node);

        retrieved_token_length = get_next_token(line_ptr, retrieved_token_id);
    }

    //TODO: Pegar nova linha caso o 1º token seja um símbolo e não tenham tokens após ele.

    // Se a linha só possui um label, lê mais linhas até formar uma linha completa.
    if ( ( (*token_list)->type == label ) && ( (*token_list)->next == NULL ) ) {
        ++(*line_count);
        // Chamada recursiva
        generate_line_tokens_list(source_file, token_list, line_count, byte_count);
    }

}


// Salva no nó o tipo do token
void define_token_type(token_t *node){
    char *temp;

    // Testa se o token possui ":" (símbolo exclusivo de labels)
    if (   ( temp = strstr(node->token_identifier, ":") ) \
        && ( temp != NULL ) \
    ){
        // Se o ":" não for o último caracter do identificador, define o tipo como "invalid".
        if ( *(temp+1) != '\0' ) node->type = invalid;

        else{
            // Remove o ":" do final do token
            *temp = '\0';

            // Se o símbolo for válido, define tipo como "label"
            if ( is_symbol(node->token_identifier) ) node->type = label;

            // Se o símbolo não for válido, define tipo como "invalid".
            else node->type = invalid;
        }
    }
    else if ( is_directive(node->token_identifier) )   node->type = directive;
    else if ( is_instruction(node->token_identifier) ) node->type = instruction;
    else if ( is_symbol(node->token_identifier) )      node->type = symbol;
    else if ( is_number(node->token_identifier) )      node->type = number;
    else if ( is_char(node->token_identifier, ",") )   node->type = comma;
    else if ( is_char(node->token_identifier, "+") )   node->type = plus;
    else if ( is_char(node->token_identifier, "-") )   node->type = minus;
    else node->type = invalid;
}


// Testa se o token é um símbolo
int is_symbol(char *id){
    char temp[ MAX_IDENTIFIER_WIDTH ];
    char garbage_start, garbage_end;

    garbage_start = garbage_end = '\0';

    // Scanset definido:
    // %*[0-9]: ignora números no início da string;
    // %[_A-Z0-9]: lê o restante da string e para de ler se encontrar um caracter inválido;
    // %*s: ignora o restante da linha, caso existir.
    // sscanf(id, "%1[0-9]%[A-Z0-9_]%c", &garbage_start, temp, &garbage_end);
    sscanf(id, "%1[0-9]", &garbage_start);
    sscanf(id, "%1[^A-Za-z0-9_]", &garbage_end);
    sscanf(id, "%[A-Za-z0-9_]", temp);

    // Se temp == id, retorna 1. Senão, retorna 0.
    if ( (garbage_start == '\0') && (garbage_end == '\0') ) return 1;
    else return 0;  // Falso
}


// Testa se o token é um número
int is_number(char *id){
    int temp;

    // Se o retorno de sscanf for diferente de zero, significa que a string lida não é um número.
    if ( ( id == strstr(id, "0X") ) \
        && ( sscanf(id, "%X", &temp) ) ) return 1;
    else if ( ( sscanf(id, "%d", &temp) ) )   return 1;
    else return 0; // Falso
}


// Testa se o token é igual ao caracter fornecido
int is_char(char *id, const char *character){
    if ( ( strstr(id, character) == id ) && ( strlen(id) == 1 ) ) return 1;
    else return 0; // Falso
}


// Testa se o token é uma diretiva
int is_directive(char *id){
    if ( !(strcmp(id, "SECTION")) )     return 1;
    else if ( !(strcmp(id, "SPACE")) )  return 1;
    else if ( !(strcmp(id, "CONST")) )  return 1;
    else if ( !(strcmp(id, "EQU")) )    return 1;
    else if ( !(strcmp(id, "IF")) )     return 1;
    else if ( !(strcmp(id, "MACRO")) )  return 1;
    else if ( !(strcmp(id, "END")) )    return 1;
    else if ( !(strcmp(id, "TEXT")) )   return 1;
    else if ( !(strcmp(id, "DATA")) )   return 1;
    else return 0; // Falso
}


// Testa se o token é uma istrução
int is_instruction(char *id){
    if ( !(strcmp(id, "ADD")) )         return 1;
    else if ( !(strcmp(id, "SUB")) )    return 1;
    else if ( !(strcmp(id, "MULT")) )   return 1;
    else if ( !(strcmp(id, "DIV")) )    return 1;
    else if ( !(strcmp(id, "JMP")) )    return 1;
    else if ( !(strcmp(id, "JMPN")) )   return 1;
    else if ( !(strcmp(id, "JMPP")) )   return 1;
    else if ( !(strcmp(id, "JMPZ")) )   return 1;
    else if ( !(strcmp(id, "COPY")) )   return 1;
    else if ( !(strcmp(id, "LOAD")) )   return 1;
    else if ( !(strcmp(id, "STORE")) )  return 1;
    else if ( !(strcmp(id, "INPUT")) )  return 1;
    else if ( !(strcmp(id, "OUTPUT")) ) return 1;
    else if ( !(strcmp(id, "STOP")) )   return 1;
    else return 0; // Falso
}


// Converte as letras minúsculas para maiúsculas.
void convert_string_to_all_caps(char *id){
    char *temp;

    for ( temp = id ; *temp != '\0' ; temp++ ){
        if ( ( *temp >= 'a' ) && ( *temp <= 'z' ) ) *temp = *temp - 32;
    }
}


// Insere novo nó na lista;
// Retorna um ponteiro para o elemento recém-adicionado;
token_t * insert_node_at_list_end(token_t **token_list, char *retrieved_token_id, int line_count, int byte_count){

    token_t *temp = NULL;
    token_t *new_node = (token_t*) malloc(sizeof(token_t));

    // Inicializa novo token
    strcpy(new_node->token_identifier, retrieved_token_id);
    new_node->type = undefined;
    new_node->source_file_line = line_count;
    new_node->output_file_byte = -1;
    new_node->next = NULL;

    if ( *token_list == NULL ) {
        *token_list = new_node;
        new_node->prev = NULL;
    }
    else {
        temp = *token_list;
        while ( temp->next != NULL ) temp = temp->next;
        temp->next = new_node;
        new_node->prev = temp;
    }

    return new_node;
}


// Desaloca lista
void erase_token_list(token_t **token_list){
    token_t *temp = NULL;

    while ( *token_list != NULL ){
        temp = (*token_list)->next;
        free(*token_list);
        *token_list = temp;
    }
    token_list = NULL;
}


// Converte string para inteiro.
int convert_string_to_int(char *id){
    int temp;

    if ( (*(id+1) == 'X') || (*(id+2) == 'X') ) sscanf(id, "%x", &temp);
    else sscanf(id, "%d", &temp);

    return temp;
}


// Insere novo nó na tabela. Se o símbolo já existir, sobrescreve seu valor
// Retorna 0 em caso de sucesso e 1 se o símbolo já existir na tabela.
int insert_label_into_symbol_table(symbol_table_t **symbol_table, char *id, int value){

    symbol_table_t *temp, *hold;
    symbol_table_t *new_node = (symbol_table_t*) malloc(sizeof(symbol_table_t));

    strcpy(new_node->symbol, id);
    new_node->value = value;
    new_node->next  = NULL;

    temp = *symbol_table;

    if ( temp == NULL ){
        // Insere novo símbolo na tabela.
        *symbol_table = new_node;

        return 0;
    }

    // Procura se o símbolo já foi definido anteriormente.
    while ( temp != NULL ){
        if ( !( strcmp( temp->symbol, id ) ) ){
            strcpy(temp->symbol, id);
            return 1;
        }
        hold = temp;
        temp = temp->next;
    }

    // Insere novo símbolo na tabela.
    hold->next = new_node;

    return 0;
}


// Desaloca tabela de símbolos
void erase_symbol_table(symbol_table_t *symbol_table){
    symbol_table_t *temp;

    while ( symbol_table ){
        temp = symbol_table;
        symbol_table = symbol_table->next;
        free(temp);
    }
}


// Procura símbolo na tabela.
// Retorna 0 caso o símbolo não tenha sido declarado. Senão, retorna 1.
int retrieve_symbol_from_table(symbol_table_t *symbol_table, char *id, int *value){

    symbol_table_t *temp;

    temp = symbol_table;

    // Procura se o símbolo já foi definido anteriormente.
    while ( temp ){
        if ( !( strcmp( temp->symbol, id ) ) ){
            *value = temp->value;
            return 1;
        }
        temp = temp->next;
    }

    // Retorna 0 caso o símbolo não exista na tabela.
    return 0;
}


// Escreve linha no arquivo de saída.
void write_line_into_output(token_t *token_list, FILE *output_ptr){
    token_t *temp = token_list;

    while ( temp != NULL ){
        fprintf(output_ptr, "%s", temp->token_identifier);
        if ( temp->type == label ) fprintf(output_ptr, ":");
        if ( ( temp = temp->next ) != NULL  ) fprintf(output_ptr, " ");
    }
    fprintf(output_ptr, "\n");
}


// Salva lista em um arquivo binário
void save_list_into_file(token_t *token_list, FILE *binary_ptr){
    token_t *temp;

    temp = token_list;

    while ( temp != NULL ){
        fwrite(temp, sizeof(token_t), 1, binary_ptr);
        temp = temp->next;
    }

}


// Troca símbolos já definidos por sua definição
void replace_equ_defined_symbols(token_t *token_list, symbol_table_t *symbol_table){
    token_t *temp;
    int value, status;

    temp = token_list;

    while ( temp != NULL ){

        if ( temp->type == symbol ){
            status = retrieve_symbol_from_table( \
                        symbol_table, \
                        temp->token_identifier, \
                        &value);

            if ( status == 1 ){
                temp->type = number;
                sprintf(temp->token_identifier, "%d", value);
            }
        }
        temp = temp->next;
    }
}






// #endif precisa ser a última linha
#endif
