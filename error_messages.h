////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////


// Testa se o cabeçalho já foi incluso. Se não, o inclui.
#ifndef ERROR_MESSAGES_HEADER
#define ERROR_MESSAGES_HEADER


#define MAN_MESSAGE "\
*************************************************************\n\
*********         Montador Pseudo-Assembly          *********\n\
*************************************************************\n\n\
                    Argumentos inválidos!\n\n\
  Modo de uso:\n\
   > %s -p <source_file> <output_file>\n\
     Pré-processamento do código.\n\
       - <source_file> deve ter extensão .asm;\n\
       - <output_file> deve ter extensão .o;\n\
       - <output_file> será concatenado com a \
extensão .pre .\n\n\
   > %s -m <source_file> <output_file>\n\
     Processamento de macros.\n\
       - <source_file> deve ter extensão .asm;\n\
       - <output_file> deve ter extensão .o;\n\
       - <output_file> será concatenado com a \
extensão .mcr .\n\n\
   > %s -o <source_file> <output_file>\n\
     Realiza a montagem do código.\n\
       - <source_file> deve ter extensão .asm;\n\
       - <output_file> deve ter extensão .o . \n\n\
*************************************************************\n"


#define SYMBOL_NOT_DECLARED "[ERRO SEMÂNTICO] Uso de símbolo indefinido na linha %d.\n"


#define SYMBOL_REDEFINED "[ERRO SEMÂNTICO] Símbolo redefinido na linha %d. \
O valor definido anteriormente foi sobrescrito.\n"


#define EQU_TOO_MUCH_ARGUMENTS "[ERRO SINTÁTICO] Diretiva EQU com argumentos demais na linha %d. Os argumentos excedentes foram ignorados.\n"


#define EQU_INVALID_ARGUMENT "[ERRO SINTÁTICO] Operando inválido para diretiva EQU na linha %d. A diretiva foi ignorada.\n"







#endif
