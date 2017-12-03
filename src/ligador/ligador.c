////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
//                   Rebeca Hellen               13/0145068   //
////////////////////////////////////////////////////////////////
//                          Ligador                           //
////////////////////////////////////////////////////////////////

#include "functions.h"


int main(int argc, char const *argv[]) {

    // Informações retiradas dos arquivos
    int  module_size[3];
    char module_name[3][ MAX_IDENTIFIER_WIDTH + 1 ];
    char *module_reloc[3];
    FILE *source_ptr[3];
    usage_table_t *usage_table[3] = { NULL };
    definition_table_t *def_table[3] = { NULL };


    // Outras variáveis
    int iterator;


    if ( invalid_arguments(argc, argv) ){
        exit(1);
    }


    for ( iterator = 0 ; ( iterator < (argc - 1) ) ; iterator++ ){

        source_ptr[ iterator ] = fopen(argv[ iterator + 1 ], "r");
        if ( source_ptr[ iterator ] == NULL ){
            printf("\n Houve um erro ao abrir o arquivo %s !\n", argv[ iterator + 1 ]);
            exit(1);
        }

        read_file_name_from_header( module_name[ iterator ], source_ptr[ iterator ] );

        read_file_size_from_header( &module_size[ iterator ], source_ptr[ iterator ] );

        read_bitstream_from_header( &module_reloc[ iterator ], module_size[ iterator ], source_ptr[ iterator ] );

        reconstruct_symbol_tables( &usage_table[ iterator ], &def_table[ iterator ], source_ptr[ iterator ] );
    }

    while ( iterator < 3 ){
        module_size[ iterator ]     = 0;
        *module_name[ iterator ]    = '\0';
        module_reloc[ iterator ]    = NULL;
        source_ptr[ iterator ]      = NULL;
        usage_table[ iterator ]     = NULL;
        def_table[ iterator ]       = NULL;
        iterator++;
    }





    for ( iterator = 0 ; ( iterator < (argc - 1) ) ; iterator++ ){
        fclose( source_ptr[ iterator ] );
    }

    // TODO: Liberar memória das tabelas e bitstream de relocação.

    return 0;
}
