////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
//   Preprocessamento: Somente avalia as diretivas EQU e IF.  //
////////////////////////////////////////////////////////////////

void read_file_line(FILE *input_file, char *output_string){
    fscanf(input_file, "%[^;\n]%*[^\n]%*c", output_string);
}
