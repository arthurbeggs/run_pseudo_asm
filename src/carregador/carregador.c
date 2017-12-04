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


    // Simula o código
    simulate( file_content, file_size );



    // TODO: Dividir em chunks

    // TODO: Criar imagem de memória



    fclose( source_ptr );

    return 0;
}
