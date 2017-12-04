////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
//                   Rebeca Hellen               13/0145068   //
////////////////////////////////////////////////////////////////

// Testa se o cabeçalho já foi incluso. Se não, o inclui.
#ifndef FUNCTIONS3_HEADER
#define FUNCTIONS3_HEADER


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


/////////////////////////
// Definições de tipos //
/////////////////////////



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


// Lê words do arquivo executável
void read_content_from_executable(int *content, int size, FILE *file_ptr);


// Simula o código do arquivo executável
void simulate(const int *content, int size);


////////////////////
// Implementações //
////////////////////

// Valida argumentos passados por linha de comando
// Retorna 1 para argumentos inválidos e 0 para argumentos válidos
int invalid_arguments(int argc, char const *argv[]){

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

// Lê words do arquivo executável
void read_content_from_executable(int *content, int size, FILE *file_ptr) {

    int iterator = 0;

    fscanf( file_ptr, "%*[^:]" );
    fscanf( file_ptr, "%*[:]" );

    while ( iterator < size ) {

        fscanf(file_ptr, " %d", &content[ iterator ]);
        iterator++;
    }
}


// Simula o código do arquivo executável
void simulate(const int *content, int size) {

    int ACC = 0;
    int PC  = 0;

    // Cria uma cópia modificável do conteúdo do arquivo
    int *data = (int *) malloc( size * sizeof(int) );
    memcpy( data, content, ( size * sizeof(int) ) );

    while ( PC < size ){
        if ( PC > size ){
            // TODO: Mensagem de erro out of bounds
        }
        switch ( data[ PC ] ) {
            case 1 :    // ADD
                // printf("ADD\n");
                ACC += data[ data[ PC + 1 ] ];
                PC += 2;
                break;

            case 2 :    // SUB
                // printf("SUB\n");
                ACC -= data[ data[ PC + 1 ] ];
                PC += 2;
                break;

            case 3 :    // MULT
                // printf("MULT\n");
                ACC = ACC * data[ data[ PC + 1 ] ];
                PC += 2;
                break;

            case 4 :    // DIV
                // printf("DIV\n");
                ACC = ACC / data[ data[ PC + 1 ] ];
                PC += 2;
                break;

            case 5 :    // JMP
                // printf("JMP\n");
                PC = data[ PC + 1 ];
                break;

            case 6 :    // JMPN
                // printf("JMPN\n");
                if ( ACC < 0 ) PC = data[ PC + 1 ];
                PC += 2;
                break;

            case 7 :    // JMPP
                // printf("JMPP\n");
                if ( ACC > 0 ) PC = data[ PC + 1 ];
                PC += 2;
                break;

            case 8 :    // JMPZ
                // printf("JMPZ\n");
                if ( ACC == 0 ) PC = data[ PC + 1 ];
                PC += 2;
                break;

            case 9 :    // COPY
                // printf("COPY\n");
                data[ PC + 2 ] = data[ PC + 1 ];
                PC += 3;
                break;

            case 10 :   // LOAD
                // printf("LOAD\n");
                ACC = data[ PC + 1 ];
                PC += 2;
                break;

            case 11 :   // STORE
                // printf("STORE\n");
                data[ PC + 1 ] = ACC;
                PC += 2;
                break;

            case 12 :   // INPUT
                // printf("INPUT\n");
                scanf("%d", &data[ PC + 1 ]);
                PC += 2;
                break;

            case 13 :   // OUTPUT
                // printf("OUTPUT\n");
                printf("%d\n", data[ PC + 1 ]);
                PC += 2;
                break;

            case 14 :   // STOP
                // Encerra simulação
                // printf("STOP\n");
                free( data );
                return;

                break;

            default :
                // TODO: Mensagem de instrução inválida
                break;
        }
    }

    free( data );
}



// #endif precisa ser a última linha
#endif
