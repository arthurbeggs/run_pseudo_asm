#include <stdio.h>
#include <string.h>

char const * man_message = "*****************************************\n\
****    Montador Pseudo-Assembly     ****\n\
*****************************************\n\n\
Modo de uso:\n\
\t > ./assembler -p <source_file> <output_file>\n\
\t\t Pré-processamento do código.\n\
\t\t   - <source_file> deve ter extensão .asm;\n\
\t\t   - <output_file> deve ter extensão .o;\n\
\t\t   - <output_file> será concatenado com a \
extensão .pre .\n\n\
\t > ./assembler -m <source_file> <output_file>\n\
\t\t Processamento de macros.\n\
\t\t   - <source_file> deve ter extensão .asm;\n\
\t\t   - <output_file> deve ter extensão .o;\n\
\t\t   - <output_file> será concatenado com a \
extensão .mcr .\n\n\
\t > ./assembler -o <source_file> <output_file>\n\
\t\t Realiza a montagem do código.\n\
\t\t   - <source_file> deve ter extensão .asm;\n\
\t\t   - <output_file> deve ter extensão .o . \n\n\
*****************************************\n";


int valid_command(int, char const **);
