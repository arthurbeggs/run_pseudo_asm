////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
//                   Rebeca Hellen               13/0145068   //
////////////////////////////////////////////////////////////////
//                         Carregador                         //
////////////////////////////////////////////////////////////////

#include "functions.h"


int main(int argc, char const *argv[]) {

    // Informações retiradas do arquivo
    int  file_size;
    int *file_content;
    char file_name[ MAX_IDENTIFIER_WIDTH + 1 ];
    char *file_reloc;
    FILE *source_ptr;

    // Outras variáveis
    chunk_table_t *chunk_table = NULL;
    int available_space = 0;    // Em bytes
    int selected_chunk_addr;
    char temp_string[ MAX_IDENTIFIER_WIDTH + 1 ];
    FILE *output_ptr;
    int iterator = 0;


    if ( invalid_arguments(argc, argv) ){
        exit(1);
    }

    source_ptr = fopen(argv[ 1 ], "r");
    if ( source_ptr == NULL ){
        printf("\n Houve um erro ao abrir o arquivo %s !\n", argv[ 1 ]);
        exit(1);
    }

    read_file_name_from_header( file_name, source_ptr );

    read_file_size_from_header( &file_size, source_ptr );

    read_bitstream_from_header( &file_reloc, file_size, source_ptr );

    file_content = (int *) malloc( file_size * sizeof(int) );

    read_content_from_executable( file_content, file_size, source_ptr );

    fclose( source_ptr );


    // Simula o código
    simulate( file_content, file_size );

    available_space = create_chunk_table( &chunk_table, argv );

    if ( ( available_space - (file_size * 2) ) < 0 ) {
        printf(OUT_OF_MEM);
        exit(1);
    }

    // Cria o arquivo de saída em modo escrita.
    strcpy(temp_string, argv[ 1 ]);
    strcat(temp_string, ".im");
    output_ptr = fopen(temp_string, "w");
    if ( output_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo %s !\n", temp_string);
        exit(1);
    }


    selected_chunk_addr = search_big_enough_chunk(chunk_table, (file_size * 2));

    // Escreve a memória em mais de 1 chunk
    if ( selected_chunk_addr == -1 ) {








    }

    // Escreve a memória em um único chunk
    else {
        for ( iterator = 0; iterator < file_size; iterator++ ) {
            if ( file_reloc[ iterator ] == '0' ){
                fprintf( output_ptr, " %d", file_content[ iterator ] );
            }

            else {
                fprintf( output_ptr, " %d", (file_content[ iterator ] + selected_chunk_addr) );
            }
        }
    }

    fclose(output_ptr);

    return 0;
}
