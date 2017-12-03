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


// Gera tabela de uso



// Gera tabela de definição



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





// #endif precisa ser a última linha
#endif
