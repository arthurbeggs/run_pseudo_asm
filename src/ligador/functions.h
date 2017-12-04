////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
//                   Rebeca Hellen               13/0145068   //
////////////////////////////////////////////////////////////////

// Testa se o cabeçalho já foi incluso. Se não, o inclui.
#ifndef FUNCTIONS2_HEADER
#define FUNCTIONS2_HEADER


//////////////
// Includes //
//////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//////////////////////////
// Definições de macros //
//////////////////////////

#define MAX_IDENTIFIER_WIDTH 100

#define MAN_MESSAGE "\
*************************************************************\n\
*********          Ligador Pseudo-Assembly          *********\n\
*************************************************************\n\n\
                    Argumentos inválidos!\n\n\
  Modo de uso:\n\
   > %s <object_file> ...\n\
     Realiza a montagem do código.\n\
     Podem ser fornecidos de 1 a 3 <object_file> com extensão \".o\".\n\n\
                  A execução será abortada!\n\n\
*************************************************************\n"


/////////////////////////
// Definições de tipos //
/////////////////////////

typedef struct address_vector_t{
    int value;
    struct address_vector_t *next;
}address_vector_t;

typedef struct definition_table_t{
    char symbol[ MAX_IDENTIFIER_WIDTH + 1 ];
    int value;
    struct definition_table_t *next;
}definition_table_t;

typedef struct usage_table_t{
    char symbol[ MAX_IDENTIFIER_WIDTH + 1 ];
    struct address_vector_t *address;
    struct usage_table_t *next;
}usage_table_t;



///////////////////////////
// Protótipos de funções //
///////////////////////////

// Valida argumentos passados por linha de comando
// Retorna 1 para argumentos inválidos e 0 para argumentos válidos
int invalid_arguments(int argc, char const *argv[]);


// Lê nome do arquivo no cabeçalho
void read_file_name_from_header(char *string, FILE *file_ptr);


// Lê tamanho do arquivo no cabeçalho
void read_file_size_from_header(int *size, FILE *file_ptr);


// Lê bitstream de relocação no cabeçalho
void read_bitstream_from_header(char **string, int size, FILE *file_ptr);


// Reconstrói tabelas de uso e de definição
void reconstruct_symbol_tables(usage_table_t **usage, definition_table_t **definition, FILE *file_ptr);


// Adiciona entrada ao final da tabela de uso
void insert_usage_entry(usage_table_t **table, FILE *file_ptr);


// Adiciona entrada ao final da tabela de definição
void insert_definition_entry(definition_table_t **table, FILE *file_ptr);


// Adiciona entrada ao final do vetor de endereços
void insert_address_entry(address_vector_t **vector, int value);


// Atualiza endereços na tabela de uso
void update_usage_addresses(usage_table_t **table, int offset);


// Atualiza endereços na tabela de definição
void update_definition_addresses(definition_table_t **table, int offset);


// Copia words do arquivo .o para um arquivo binário temporário
void copy_words_to_bin_file(FILE *dest, FILE *src, char *bitmap, int offset, usage_table_t *table);


// Passa words do arquivo binário para o arquivo de texto
void parse_bin_file_to_text(FILE *txt, FILE *bin);


// Resolve referências a outros módulos
void solve_address_references(usage_table_t **usage_tables, definition_table_t **def_tables, FILE *file_ptr);

// Procura se posição de memória é referenciada na tabela de uso
// Retorna 1 se houver referência na tabela
int is_address_in_usage_table(int address, usage_table_t *table);



////////////////////
// Implementações //
////////////////////

// Valida argumentos passados por linha de comando
// Retorna 1 para argumentos inválidos e 0 para argumentos válidos
int invalid_arguments(int argc, char const *argv[]){
    char const *temp;
    int count;

    if ( ( argc < 2 ) || ( argc > 4 ) ){
        printf( MAN_MESSAGE, argv[0] );
        return 1;
    }

    for ( count = 1; count < argc; count++ ) {
        if ( !( temp = strstr(argv[count], ".o") ) || ( *(temp+2) != '\0') ){
            printf( MAN_MESSAGE, argv[0] );
            return 1;
        }
    }
    return 0;
}


// Lê nome do arquivo no cabeçalho
void read_file_name_from_header(char *string, FILE *file_ptr){
    fscanf(file_ptr, "%*[^ ]");
    fscanf(file_ptr, " %100[^\n]", string);
    fscanf(file_ptr, "%*1[\n]");
}


// Lê tamanho do arquivo no cabeçalho
void read_file_size_from_header(int *size, FILE *file_ptr){
    fscanf(file_ptr, "%*[^ ]");
    fscanf(file_ptr, " %d", size);
    fscanf(file_ptr, "%*1[\n]");
}


// Lê bitstream de relocação no cabeçalho
void read_bitstream_from_header(char **string, int size, FILE *file_ptr){
    *string = (char*) malloc( (size + 1) * sizeof(char) );

    fscanf(file_ptr, "%*[^ ]");
    fscanf(file_ptr, " %[^\n]", *string);
    fscanf(file_ptr, "%*1[\n]");
}


// Reconstrói tabelas de uso e de definição
void reconstruct_symbol_tables(usage_table_t **usage, definition_table_t **definition, FILE *file_ptr){

    char header_label[3];

    while ( 1 ){
        fscanf(file_ptr, "%2[^:]", header_label);
        fscanf(file_ptr, "%*[ :]");

        if ( !( strcmp(header_label, "TU") ) ) {
            insert_usage_entry( usage, file_ptr );
        }
        else if ( !( strcmp(header_label, "TD") ) ) {
            insert_definition_entry( definition, file_ptr );
        }
        else break;
    }
}


// Adiciona entrada ao final da tabela de uso
void insert_usage_entry(usage_table_t **table, FILE *file_ptr){

    int value;

    usage_table_t *temp        = NULL;
    usage_table_t *new_node    = (usage_table_t*) malloc(sizeof(usage_table_t));

    fscanf(file_ptr, "%100[^\n ]", new_node->symbol);
    new_node->next      = NULL;
    new_node->address   = NULL;


    if ( *table == NULL ) {
        *table = new_node;
    }

    else {
        temp = *table;
        while ( temp->next != NULL ) temp = temp->next;
        temp->next = new_node;
    }

    while ( fscanf(file_ptr, " %d", &value) ){
        insert_address_entry( &(new_node->address), value );
    }

}


// Adiciona entrada ao final da tabela de definição
void insert_definition_entry(definition_table_t **table, FILE *file_ptr){

    definition_table_t *temp        = NULL;
    definition_table_t *new_node    = (definition_table_t*) malloc(sizeof(definition_table_t));

    fscanf(file_ptr, "%100[^\n ]", new_node->symbol);
    fscanf(file_ptr, " %d", &(new_node->value));
    fscanf(file_ptr, "%*1[\n]");
    new_node->next = NULL;

    if ( *table == NULL ) {
        *table = new_node;
    }

    else {
        temp = *table;
        while ( temp->next != NULL ) temp = temp->next;
        temp->next = new_node;
    }
    return;

}


// Adiciona entrada ao final do vetor de endereços
void insert_address_entry(address_vector_t **vector, int value){

    address_vector_t *temp      = NULL;
    address_vector_t *new_node  = (address_vector_t*) malloc(sizeof(address_vector_t));

    new_node->value = value;
    new_node->next  = NULL;

    if ( *vector == NULL ){
        *vector = new_node;
    }

    else {
        temp = *vector;
        while ( temp->next != NULL ) temp = temp->next;
        temp->next = new_node;
    }
}


// Atualiza endereços na tabela de uso
void update_usage_addresses(usage_table_t **table, int offset) {

    usage_table_t *temp      = *table;
    address_vector_t *vector = NULL;

    while ( temp != NULL ){
        vector = temp->address;
        while( vector != NULL ){
            vector->value += offset;
            vector = vector->next;
        }

        temp = temp->next;
    }
}


// Atualiza endereços na tabela de definição
void update_definition_addresses(definition_table_t **table, int offset) {

    definition_table_t *temp = *table;

    while ( temp != NULL ){
        temp->value += offset;
        temp = temp->next;
    }
}


// Copia words do arquivo .o para um arquivo binário temporário
void copy_words_to_bin_file(FILE *dest, FILE *src, char *bitmap, int offset, usage_table_t *table) {
    int value;
    int iterator = 0;

    while ( !(feof(src)) ) {
        fscanf(src, " %d", &value);
        if (   ( bitmap[ iterator ] == '1' ) \
           && !( is_address_in_usage_table( (iterator + offset), table ) ) \
        ) {
            value += offset;
        }
        fwrite( &value, sizeof(int), 1, dest );
        iterator++;
    }
}


// Passa words do arquivo binário para o arquivo de texto
void parse_bin_file_to_text(FILE *txt, FILE *bin){

    int temp;

    rewind(bin);
    while ( !( feof(bin) ) ){
        fread( &temp, sizeof(int), 1, bin);
        if ( feof(bin) ) break;
        fprintf(txt, " %d", temp);
    }

}


// Resolve referências a outros módulos
void solve_address_references(usage_table_t **usage_tables, definition_table_t **def_tables, FILE *file_ptr) {

    int increment = 0;
    int iterator, iterator2;
    char symbol[ MAX_IDENTIFIER_WIDTH + 1 ];
    usage_table_t *usage_ptr    = NULL;
    definition_table_t *def_ptr = NULL;
    address_vector_t *vector_ptr= NULL;
    fpos_t eof_position;

    fgetpos(file_ptr, &eof_position);

    for ( iterator = 0 ; iterator < 3 ; iterator++ ) {
        usage_ptr = usage_tables[ iterator ];
        while ( usage_ptr != NULL ) {
            strcpy(symbol, usage_ptr->symbol);
            vector_ptr = usage_ptr->address;
            for ( iterator2 = 0 ; iterator2 < 3 ; iterator2++ ) {
                if ( iterator2 == iterator ) continue;

                def_ptr = def_tables[ iterator2 ];
                while ( def_ptr != NULL ) {
                    if ( !(strcmp( symbol, def_ptr->symbol )) ){
                        while ( vector_ptr != NULL ) {
                            fseek( file_ptr, (vector_ptr->value * sizeof(int)), SEEK_SET );
                            fread( &increment, sizeof(int), 1, file_ptr );
                            fseek( file_ptr, (vector_ptr->value * sizeof(int)), SEEK_SET );
                            increment += def_ptr->value;
                            fwrite( &increment, sizeof(int), 1, file_ptr );

                            vector_ptr = vector_ptr->next;
                        }

                        fsetpos(file_ptr, &eof_position);
                        goto next_usage_entry;
                    }

                    def_ptr = def_ptr->next;
                }
            }
            next_usage_entry:
            usage_ptr = usage_ptr->next;
        }
    }
}


// Procura se posição de memória é referenciada na tabela de uso
// Retorna 1 se houver referência na tabela
int is_address_in_usage_table(int address, usage_table_t *table){

    usage_table_t *table_ptr        = table;
    address_vector_t *vector_ptr    = NULL;

    while ( table_ptr != NULL ) {
        vector_ptr = table_ptr->address;

        while ( vector_ptr != NULL ) {
            if ( vector_ptr->value == address ) return 1;

            vector_ptr = vector_ptr->next;
        }
        table_ptr = table_ptr->next;
    }

    return 0;
}



// #endif precisa ser a última linha
#endif
