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
    int offset;
    FILE *tempfile_ptr;
    FILE *output_ptr;
    char filename[ MAX_IDENTIFIER_WIDTH + 10 ];
    char *str_pointer;


    if ( invalid_arguments(argc, argv) ){
        exit(1);
    }


    offset = 0;
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

        update_usage_addresses( &usage_table[ iterator ], offset );
        update_definition_addresses( &def_table[ iterator ], offset );
        offset += module_size[ iterator ];
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

    // Cria o arquivo temporário.
    tempfile_ptr = tmpfile();
    if ( tempfile_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo temporário! \n");
        exit(1);
    }

    offset = 0;
    for ( iterator = 0 ; ( iterator < (argc - 1) ) ; iterator++ ) {
        copy_words_to_bin_file( tempfile_ptr, source_ptr[ iterator ], module_reloc[ iterator ], offset, usage_table[ iterator ] );
        fclose( source_ptr[ iterator ] );
        offset += module_size[ iterator ];
    }

    solve_address_references( usage_table, def_table, tempfile_ptr );

    // Cria o arquivo de saída
    strcpy(filename, argv[1]);
    str_pointer = strstr(filename, ".o");
    *str_pointer = '\0';

    output_ptr = fopen(filename, "w");
    if ( output_ptr == NULL ){
        printf("\n Houve um erro ao criar o arquivo %s !\n", filename);
        exit(1);
    }

    // Escreve arquivo de saída
    fprintf(output_ptr, "H: %s\n", module_name[0]);

    offset = module_size[0] + module_size[1] + module_size[2];

    fprintf(output_ptr, "H: %d\n", offset); // Tamanho do código

    fprintf(output_ptr, "H: ");
    for ( iterator = 0 ; ( iterator < (argc - 1) ) ; iterator++ ) {
        fprintf(output_ptr, "%s", module_reloc[ iterator ]);
    }

    fprintf(output_ptr, "\nT:");
    parse_bin_file_to_text(output_ptr, tempfile_ptr);

    fclose(tempfile_ptr);
    fclose(output_ptr);

    // TODO: Liberar memória das tabelas e bitstream de relocação.

    return 0;
}
