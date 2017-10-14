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


#define SYMBOL_NOT_DECLARED "[ERRO SEMÂNTICO] Uso de símbolo indefinido na linha %d.\n" //declarações e rótulos ausentes;


#define SYMBOL_REDEFINED "[ERRO SEMÂNTICO] Símbolo redefinido na linha %d. O valor definido anteriormente foi sobrescrito.\n"


#define MACRO_REDEFINED "[ERRO SEMÂNTICO] Macro redefinida na linha %d. A definição atual será ignorada.\n"


#define EQU_TOO_MUCH_ARGUMENTS "[ERRO SINTÁTICO] Diretiva EQU com argumentos demais na linha %d. Os argumentos excedentes foram ignorados.\n"


#define EQU_INVALID_ARGUMENT "[ERRO SINTÁTICO] Operando inválido para diretiva EQU na linha %d. A diretiva foi ignorada.\n"


#define DECLARACAO_OU_ROTULO_REPETIDO "[ERRO SINTÁTICO] Declaração e /ou rótulo repetido na linha %d.\n"// declarações e rótulos repetidos;


#define JUMP_ROTULO_INEXISTENTE "[ERRO SEMÂNTICO] Pulo para rótulo inexistente na linha %d.\n"// pulo para rótulos inexistente;


#define JUMP_ROTULO_INVALIDO "[ERRO SEMÂNTICO] Pulo para rótulo inválido na linha %d.\n"// pulo para rótulos inválidos;


#define JUMP_SECAO_ERRADA "[ERRO SEMÂNTICO] Pulo para seção errada na linha %d. \n"// pulo para seção errada;


#define DIRETIVA_INVALIDA "[ERRO SINTÁTICO] Diretiva inválida na linha %d. \n"// diretivas inválidas;


#define INSTRUCAO_INVALIDA "[ERRO SINTÁTICO] Instrução inválida na linha %d. \n"// instruções inválidas;


#define DIRETIVA_OU_INSTRUCAO_NA_SECAO_ERRADA "[ERRO SINTÁTICO] Diretivas ou instruções na seção errada na linha %d. \n"// diretivas ou instruções na seção errada;


#define DIV_POR_ZERO "[ERRO SEMÂNTICO] Divisão por zero na linha %d. \n"// divisão por zero (para constante);


#define QTD_OPERANDO_INVALIDO "[ERRO SINTÁTICO ] Instruções com a quantidade de operando inválida na linha %d. \n"// instruções com a quantidade de operando inválida;


#define TOKENS_INVALIDOS "[ERRO LÉXICO] Tokens inválidos na linha %d. \n"// tokens inválidos;


#define DOIS_ROTULOS_NA_MESMA_LINHA "[ERRO SINTÁTICO] Dois rótulos na mesma linha na linha %d. \n"// dois rótulos na mesma linha;


#define SECTION_TEXT_FALTANDO "[ERRO SINTÁTICO] Seção text inexistente. \n"// seção TEXT faltante;


#define SECTION_INVALIDA "[ERRO SINTÁTICO] Seção inválida na linha %d. \n"// seção inválida;


#define TIPO_DE_ARGUMENTO_INVALIDO "[ERRO SEMÂNTICO] Tipo de argumento inválido na linha %d. \n"// tipo de argumento inválido;


#define MODIFICACAO_DE_UM_VALOR_CTE "[ERRO SEMÂNTICO] Modificação de um valor constante na linha %d. \n"// modificação de um valor constante;


#define EOF_REACHED_BEFORE_END "[ERRO SINTÁTICO] O arquivo chegou ao fim sem encontrar a diretiva END da macro %s.\n\nO programa foi abortado com erros!\n"



#endif
