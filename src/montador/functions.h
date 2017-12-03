////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
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
    char token_id[ MAX_IDENTIFIER_WIDTH +1 ];
    token_type type;        // Tipo do token;
    int source_file_line;   // Linha do arquivo original;
    int output_file_byte;   // Posição de memoria no arquivo de saída;
    struct token_t *prev;   // Ponteiro para o token anterior;
    struct token_t *next;   // Ponteiro para o próximo token;
}token_t;


typedef struct symbol_table_t{
    char symbol[ MAX_IDENTIFIER_WIDTH + 1 ];
    int  value;
    struct symbol_table_t *next;
}symbol_table_t;


typedef struct macro_def_table_t{
    token_t *macro_line;  //lista que contem a definição da macro;
    struct macro_def_table_t *next;   // Ponteiro para a proxima linha da mnt;
}macro_def_table_t;


typedef struct macro_name_table_t{
    char symbol[ MAX_IDENTIFIER_WIDTH + 1 ]; // Nome da macro (label da macro)
    struct macro_def_table_t *definition;
    struct macro_name_table_t *next;   // Ponteiro para a proxima linha da mnt;
}macro_name_table_t;


typedef struct address_vector_t{
    int value;
    struct address_vector_t *next;
}address_vector_t;


typedef struct assembler_symbol_table_t{
    char symbol[ MAX_IDENTIFIER_WIDTH + 1 ];
    int  defined;            // Diz se o simbolo já foi definido ou não
    int  value;              // Endereço do símbolo
    int  public_symbol;
    int  extern_symbol;
    struct address_vector_t *address;
    struct assembler_symbol_table_t *next;   // Proxima linha da tabela
}assembler_symbol_table_t;



// Protótipos de funções


// Avalia se os argumentos passados ao programa estão corretos.
// Retorna 0 se os argumentos passados não estiverem corretos. Se estiverem, retorna 1.
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


// Recupera lista de tokens de uma linha
void retrieve_token_list_from_file(token_t **token_list, FILE *binary_ptr);


// Insere novo label na MNT;
// Retorna 0 em caso de sucesso e 1 se o símbolo já existir na tabela.
int insert_label_into_macro_name_table(macro_name_table_t **macro_table, char *symbol, macro_name_table_t **table_node);


// Insere nova linha de tokens na MDT.
void insert_line_into_macro_def_table(macro_name_table_t **macro_name_node, token_t **token_list);


// Recupera entrada da MNT
void retrieve_macro_from_table( macro_name_table_t **macro_table, char *symbol, macro_name_table_t **retrieved_node );


// Apaga a tabela de definições de macro, liberando memória.
void erase_macro_table( macro_name_table_t **macro_table );


// Apaga a tabela de símbolos de montagem, liberando memória
void erase_assembler_symbol_table( assembler_symbol_table_t **symbol_table );


// Procura se símbolo existe na tabela.
// Retorna o endereço do símbolo já definido ou 0 apra símbolo não definido.
int check_symbol_table( assembler_symbol_table_t **table, char *symbol, int address );


assembler_symbol_table_t * define_entry_on_symbol_table( assembler_symbol_table_t **table, char *symbol, int value );


// Cria novo nó na tabela de símbolos.
// Retorna o nó criado.
assembler_symbol_table_t * create_node_at_table_end(assembler_symbol_table_t **table, char *symbol, int defined, int value, int public_symbol, int extern_symbol);


// Cria novo nó no vetor de endereços.
void create_node_at_address_vector_end(address_vector_t **addr_vector, int value);



int get_increment_value( token_t *token_list );



int convert_token_to_int(char *sym);



// Implementações

// Avalia se os argumentos passados ao programa estão corretos.
// Retorna 0 se os argumentos passados não estiverem corretos. Se estiverem, retorna 1.
int valid_command(int argc, char const *argv[]){
    char const *temp;
    int count;

    if ( ( argc < 2 ) || ( argc > 4 ) ){
        printf( MAN_MESSAGE, argv[0] );
        return 0;
    }
    for ( count = 1; count < argc; count++ ) {
        if ( !( temp = strstr(argv[count], ".asm") ) || ( *(temp+4) != '\0') ){
            printf( MAN_MESSAGE, argv[0] );
            return 0;
        }
    }
    return 1;
}


// Lê uma linha do arquivo de entrada e salva a linha no buffer fornecido.
// Retorna caso o arquivo tenha terminado.
void read_file_line(FILE *source_file, char *output_string){
    // Comportamento do scanset definido:
    // " " ignora espaços e tabs no início da linha;
    // %[^;\n] lê o restante da linha (máximo de 500 caracteres), para ao encontrar a primeira ocorrência de um comentário (;) ou um line feed (\n) e salva a string lida em output_string;
    // %*[^\n] lê o restante da linha (comentário ou nada), para ao encontrar a primeira ocorrência de um carriage return(\r) ou um line feed (\n) e descarta a string lida;
    // %*[\n] lê o identificador de final de linha e o descarta. Funciona para identificador LF;
    //NOTE: Se o tamanho da macro MAX_LINE_WIDTH for alterado (!= 500), é necessário alterar o tamanho máximo do 2º parâmetro do scanset.

    fscanf(source_file, "%*[\t ]");
    fscanf(source_file, "%500[^;\n]", output_string);
    fscanf(source_file, "%*[^\n]");
    fscanf(source_file, "%*1[\n]");
}


// Lê o primeiro token de uma linha.
// Retorna a quantidade de caracteres do token (desconsiderando '\0').
int get_next_token(char *input_line, char *output_token){
    char *temp;

    *output_token = '\0';

    // Comportamento do scanset definido:
    // %*[ \t] ignora espaços e tabs que antecedem o token;
    // %[^ \t] lê o restante da linha (máximo de 100 caracteres), para ao encontrar a primeira ocorrência de um espaço ou tab e salva a string lida em output_token (não separa tokens ",", "+" e "-" quando emendados a outros tokens);
    //NOTE: Se o tamanho da macro MAX_IDENTIFIER_WIDTH for alterado (!= 100), é necessário alterar o tamanho máximo do 2º parâmetro do scanset.
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
        convert_string_to_all_caps(last_created_node->token_id);

        define_token_type(last_created_node);

        retrieved_token_length = get_next_token(line_ptr, retrieved_token_id);
    }

    // Se a linha só possui um label, lê mais linhas até formar uma linha completa.
    if ( ( ( (*token_list) != NULL ) && (*token_list)->type == label ) && ( (*token_list)->next == NULL ) ) {
        ++(*line_count);
        // Chamada recursiva
        generate_line_tokens_list(source_file, token_list, line_count, byte_count);
    }

}


// Salva no nó o tipo do token
void define_token_type(token_t *node){
    char *temp;

    // Testa se o token possui ":" (símbolo exclusivo de labels)
    if (   ( temp = strstr(node->token_id, ":") ) \
        && ( temp != NULL ) \
    ){
        // Se o ":" não for o último caracter do identificador, define o tipo como "invalid".
        if ( *(temp+1) != '\0' ) node->type = invalid;

        else{
            // Remove o ":" do final do token
            *temp = '\0';

            // Testa se o token tem o mesmo nome de uma diretiva ou instrução
            if ( \
                    ( is_directive(node->token_id) ) \
                ||  ( is_instruction(node->token_id) ) \
            ) {
                node->type = invalid;
            }

            // Se o símbolo for válido, define tipo como "label"
            else if ( is_symbol(node->token_id) ) node->type = label;

            // Se o símbolo não for válido, define tipo como "invalid".
            else node->type = invalid;
        }
    }
    else if ( is_directive(node->token_id) )   node->type = directive;
    else if ( is_instruction(node->token_id) ) node->type = instruction;
    else if ( is_symbol(node->token_id) )      node->type = symbol;
    else if ( is_number(node->token_id) )      node->type = number;
    else if ( is_char(node->token_id, ",") )   node->type = comma;
    else if ( is_char(node->token_id, "+") )   node->type = plus;
    else if ( is_char(node->token_id, "-") )   node->type = minus;
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
    if      ( !(strcmp(id, "SECTION")) )    return 1;
    else if ( !(strcmp(id, "SPACE")) )      return 1;
    else if ( !(strcmp(id, "CONST")) )      return 1;
    else if ( !(strcmp(id, "EQU")) )        return 1;
    else if ( !(strcmp(id, "IF")) )         return 1;
    else if ( !(strcmp(id, "MACRO")) )      return 1;
    else if ( !(strcmp(id, "ENDMACRO")) )   return 1;
    else if ( !(strcmp(id, "BEGIN")) )      return 1;
    else if ( !(strcmp(id, "END")) )        return 1;
    else if ( !(strcmp(id, "TEXT")) )       return 1;
    else if ( !(strcmp(id, "DATA")) )       return 1;
    else if ( !(strcmp(id, "PUBLIC")) )     return 1;
    else if ( !(strcmp(id, "EXTERN")) )     return 1;
    else return 0; // Falso
}


// Testa se o token é uma istrução
int is_instruction(char *id){
    if      ( !(strcmp(id, "ADD")) )    return 1;
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
    strcpy(new_node->token_id, retrieved_token_id);
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
    *token_list = NULL;
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

    // Não imprime nada caso a lista esteja vazia.
    if ( temp == NULL ) return;

    while ( temp != NULL ){
        fprintf(output_ptr, "%s", temp->token_id);
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
                        temp->token_id, \
                        &value);

            if ( status == 1 ){
                temp->type = number;
                sprintf(temp->token_id, "%d", value);
            }
        }
        temp = temp->next;
    }
}


// Recupera lista de tokens de uma linha
void retrieve_token_list_from_file(token_t **token_list, FILE *binary_ptr){

    token_t *temp = *token_list;
    token_t *new_node = (token_t*) malloc(sizeof(token_t));

    fread(new_node, sizeof(token_t), 1, binary_ptr);


    while ( new_node != NULL ) {
        // Adiciona nó lido na lista.
        if ( *token_list == NULL ) {
            *token_list = new_node;
            if ( new_node->next == NULL ){
                new_node->prev = NULL;
                new_node->next = NULL;
                break;
            }
            new_node->prev = NULL;
            new_node->next = NULL;
        }
        else {
            temp = *token_list;
            while ( temp->next != NULL ) temp = temp->next;
            temp->next = new_node;
            new_node->prev = temp;

            // new_node->next ainda possui seu valor antigo e serve de indicador para parar a leitura do arquivo.
            if ( new_node->next == NULL ) break;

            // Sobrescreve ponteiro inválido
            new_node->next = NULL;
        }

        new_node = (token_t*) malloc(sizeof(token_t));
        fread(new_node, sizeof(token_t), 1, binary_ptr);
    }

}


// Insere novo label na MNT;
// Retorna 0 em caso de sucesso e 1 se o símbolo já existir na tabela.
int insert_label_into_macro_name_table(macro_name_table_t **macro_table, char *symbol, macro_name_table_t **table_node){

    macro_name_table_t *temp, *hold;
    macro_name_table_t *new_node = (macro_name_table_t*) malloc( sizeof(macro_name_table_t) );

    strcpy(new_node->symbol, symbol);
    new_node->next  = NULL;
    new_node->definition = NULL;

    temp = *macro_table;

    if ( temp == NULL ){
        // Insere novo símbolo na tabela.
        *macro_table = *table_node = new_node;

        return 0;
    }

    // Procura se o símbolo já foi definido anteriormente.
    while ( temp != NULL ){
        if ( !( strcmp( temp->symbol, symbol ) ) ){
            return 1;
        }
        hold = temp;
        temp = temp->next;
    }

    // Insere novo símbolo na tabela.
    hold->next = *table_node = new_node;

    return 0;
}


// Insere nova linah de tokens na MDT;
void insert_line_into_macro_def_table(macro_name_table_t **macro_name_node, token_t **token_list){

    macro_def_table_t *temp, *hold;
    macro_def_table_t *new_node;

    if ( *macro_name_node == NULL ){
        printf("Erro! Nó da MNT vazio!\n");
        return;
    } // ERRO!

    new_node = (macro_def_table_t*) malloc( sizeof(macro_def_table_t) );
    new_node->macro_line = *token_list;
    new_node->next = NULL;

    if ( ( temp = (*macro_name_node)->definition ) == NULL ) {
        (*macro_name_node)->definition = new_node;

        return;
    }

    while ( temp != NULL ) {
        hold = temp;
        temp = temp->next;
    }

    hold->next = new_node;
}


// Recupera entrada da MNT
void retrieve_macro_from_table( macro_name_table_t **macro_table, char *symbol, macro_name_table_t **retrieved_node ){

    macro_name_table_t *temp;

    temp = *macro_table;

    // Procura se o símbolo já foi definido anteriormente.
    while ( temp ){
        if ( !( strcmp( temp->symbol, symbol ) ) ){
            *retrieved_node = temp;
            return;
        }
        temp = temp->next;
    }
    // retrieved_node recebe NULL para símbolo não encontrado.
    retrieved_node = NULL;
}


// Apaga a tabela de definições de macro, liberando memória.
void erase_macro_table( macro_name_table_t **macro_table ){

    macro_name_table_t *temp_table;
    macro_def_table_t  *temp_definition;

    while ( *macro_table != NULL ){

        temp_table = (*macro_table)->next;

        while ( (*macro_table)->definition != NULL ){
            temp_definition = (*macro_table)->definition->next;
            erase_token_list(&((*macro_table)->definition->macro_line));
            free((*macro_table)->definition);
            (*macro_table)->definition = temp_definition;
        }

        free(*macro_table);
        *macro_table = temp_table;
    }
}



int check_symbol_table( assembler_symbol_table_t **table, char *symbol, int address ){

    assembler_symbol_table_t *table_ptr = *table;
    // assembler_symbol_table_t *prev_node = NULL;

    while ( table_ptr != NULL ){
        if ( !( strcmp( table_ptr->symbol, symbol ) ) ) {
            create_node_at_address_vector_end(&(table_ptr->address), address);
            return table_ptr->value;
        }
        // prev_node = table_ptr;
        table_ptr = table_ptr->next;
    }

    table_ptr = create_node_at_table_end( table, symbol, 0, 0, 0, 0);
    create_node_at_address_vector_end(&(table_ptr->address), address);

    return 0;
}



assembler_symbol_table_t * define_entry_on_symbol_table( assembler_symbol_table_t **table, char *symbol, int value ){

    assembler_symbol_table_t *table_ptr = *table;

    while ( table_ptr != NULL ){
        if ( !( strcmp( table_ptr->symbol, symbol ) ) ){
            table_ptr->defined = 1;
            table_ptr->value   = value;


            return table_ptr;
        }
        table_ptr = table_ptr->next;
    }

    return create_node_at_table_end( table, symbol, 1, value, 0, 0);

}

void set_table_symbol_as_public( assembler_symbol_table_t **table, char *symbol) {

    assembler_symbol_table_t *table_ptr = *table;

    while ( table_ptr != NULL ){
        if ( !( strcmp( table_ptr->symbol, symbol ) ) ){
            table_ptr->public_symbol = 1;

            return;
        }
        table_ptr = table_ptr->next;
    }

    create_node_at_table_end( table, symbol, 0, 0, 1, 0);

    return;
}


assembler_symbol_table_t * create_node_at_table_end(assembler_symbol_table_t **table, char *symbol, int defined, int value, int public_symbol, int extern_symbol){

    assembler_symbol_table_t *temp      = NULL;
    assembler_symbol_table_t *new_node  = (assembler_symbol_table_t*) malloc(sizeof(assembler_symbol_table_t));

    // Inicializa novo token
    strcpy(new_node->symbol, symbol);
    new_node->defined       = defined;
    new_node->value         = value;
    new_node->public_symbol = public_symbol;
    new_node->extern_symbol = extern_symbol;
    new_node->address       = NULL;
    new_node->next          = NULL;

    if ( *table == NULL ) {
        *table = new_node;
    }
    else {
        temp = *table;
        while ( temp->next != NULL ) temp = temp->next;
        temp->next = new_node;
    }

    return new_node;
}



void create_node_at_address_vector_end(address_vector_t **addr_vector, int value){

    address_vector_t *temp      = NULL;
    address_vector_t *new_node  = (address_vector_t*) malloc(sizeof(address_vector_t));

    new_node->value = value;
    new_node->next  = NULL;

    if ( *addr_vector == NULL ){
        *addr_vector = new_node;
    }
    else {
        temp = *addr_vector;
        while ( temp->next != NULL ) temp = temp->next;
        temp->next = new_node;
    }
}



int get_increment_value( token_t *token_list ){
    if ( ( token_list != NULL ) && ( token_list->next != NULL ) ) {
        if ( token_list->type == plus ){
            return ( convert_token_to_int(token_list->next->token_id) );
        }

        else if ( token_list->type == minus ){
            return - ( convert_token_to_int(token_list->next->token_id) );
        }
    }
    return 0;
}



int convert_token_to_int(char *sym){
    int temp;

    if ( ( sym == strstr(sym, "0X") ) && ( sscanf(sym, "%X", &temp) ) )
        return temp;
    else if ( ( sscanf(sym, "%d", &temp) ) )
        return temp;
    else
        return 0;
}



token_t * find_token_by_type(token_t *list, token_type type){

    token_t *ptr = list;

    while ( ptr != NULL ){
        if ( ptr->type == type ) break;
        ptr = ptr->next;
    }

    return ptr;
}


void save_defined_value_into_file(address_vector_t *vector, FILE *binary_ptr, int value){

    address_vector_t *ptr = vector;
    fpos_t eof_position;
    int increment = 0;

    fgetpos(binary_ptr, &eof_position);

    while ( ptr != NULL ){
        fseek( binary_ptr, (ptr->value * sizeof(int) ) , SEEK_SET);
        fread( &increment, sizeof(int), 1, binary_ptr );
        fseek( binary_ptr, (ptr->value * sizeof(int) ) , SEEK_SET);
        value += increment;
        fwrite( &value, sizeof(int), 1, binary_ptr );

        ptr = ptr->next;
    }

    fsetpos(binary_ptr, &eof_position);
}


void parse_bin_file_to_text(FILE *txt, FILE *bin){

    int temp;

    rewind(bin);
    while ( !( feof(bin) ) ){
        fread( &temp, sizeof(int), 1, bin);
        if ( feof(bin) ) break;
        fprintf(txt, " %d", temp);
    }

}


void add_char_to_bitmap(char bit, FILE *file){
    fwrite( &bit, sizeof(char), 1, file );
}


void parse_bitmap_to_text(FILE *txt, FILE *bin){

    char temp;

    rewind(bin);
    while ( !( feof(bin) ) ){
        fread( &temp, sizeof(char), 1, bin);
        if ( feof(bin) ) break;
        fprintf(txt, "%c", temp);
    }

}

void print_public_symbols_into_file(assembler_symbol_table_t *table, FILE *file){

    assembler_symbol_table_t *temp = table;

    while ( temp != NULL ){
        if ( temp->public_symbol == 1 ){
            fprintf( file, "\nTD: %s %d", temp->symbol, temp->value );
        }

        temp = temp->next;
    }

}

void print_usage_table_into_file(assembler_symbol_table_t *table, FILE *file) {

    assembler_symbol_table_t *temp  = table;
    address_vector_t *vec_index     = NULL;


    while ( temp != NULL ){
        if ( temp->extern_symbol == 1 ){
            fprintf(file, "\nTU: %s", temp->symbol);
            vec_index = temp->address;
            while ( vec_index != NULL ){
                fprintf(file, " %d", vec_index->value);

                vec_index = vec_index->next;
            }
        }

        temp = temp->next;
    }
}


void erase_address_vector(address_vector_t **vector){

    address_vector_t *temp;

    while ( *vector != NULL ){
        temp = *vector;
        *vector = (*vector)->next;
        free(temp);
    }
}

void erase_assembler_symbol_table(assembler_symbol_table_t **table){

    assembler_symbol_table_t *temp;

    while ( *table ) {
        temp = *table;
        erase_address_vector(&((*table)->address));
        *table = (*table)->next;
        free(temp);
    }

}



// #endif precisa ser a última linha
#endif
