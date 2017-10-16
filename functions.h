////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////

#define MAX_LINE_WIDTH 500


// Lê uma linha do arquivo de entrada e salva a linha no buffer fornecido.
// Retorna caso o arquivo tenha terminado.
int read_file_line(FILE *input_file, char *output_string);

// Lê um token de uma linha.
int get_next_token(char *input_line, char *output_token)
