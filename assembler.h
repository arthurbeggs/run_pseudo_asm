////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

char const * man_message = "\
*************************************************************\n\
*********         Montador Pseudo-Assembly          *********\n\
*************************************************************\n\n\
                    Argumentos inválidos!\n\n\
  Modo de uso:\n\
   > ./assembler -p <source_file> <output_file>\n\
     Pré-processamento do código.\n\
       - <source_file> deve ter extensão .asm;\n\
       - <output_file> deve ter extensão .o;\n\
       - <output_file> será concatenado com a \
extensão .pre .\n\n\
   > ./assembler -m <source_file> <output_file>\n\
     Processamento de macros.\n\
       - <source_file> deve ter extensão .asm;\n\
       - <output_file> deve ter extensão .o;\n\
       - <output_file> será concatenado com a \
extensão .mcr .\n\n\
   > ./assembler -o <source_file> <output_file>\n\
     Realiza a montagem do código.\n\
       - <source_file> deve ter extensão .asm;\n\
       - <output_file> deve ter extensão .o . \n\n\
*************************************************************\n";


int valid_command(int, char const **);
