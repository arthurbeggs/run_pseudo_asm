////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
//   Preprocessamento: Somente avalia as diretivas EQU e IF.  //
////////////////////////////////////////////////////////////////

#include "functions.h"

// Lê uma linha do arquivo de entrada e salva a linha no buffer fornecido.
// Retorna caso o arquivo tenha terminado.
int read_file_line(FILE *input_file, char *output_string){
    // Comportamento do scanset definido:
    // %*[ \t] ignora espaços e tabs no início da linha;
    // %[^;\r\n] lê o restante da linha (máximo de 500 caracteres), para ao encontrar a primeira ocorrência de um comentário (;) ou um carriage return(\r) ou um line feed (\n) e salva a string lida em output_string;
    // %*[^\r\n] lê o restante da linha (comentário ou nada), para ao encontrar a primeira ocorrência de um carriage return(\r) ou um line feed (\n) e descarta a string lida;
    // %*[\r\n] lê o identificador de final de linha e o descarta. Funciona para identificador LF, CR e CRLF;
    //NOTE: Se o tamanho da macro MAX_LINE_WIDTH for alterado (!= 500), é necessário alterar o tamanho máximo do 2º parâmetro do scanset.

    return fscanf(input_file, "%*[ \t]%500[^;\r\n]%*[^\r\n]%*[\r\n]",  output_string);
}


// Lê um token de uma linha.
int get_next_token(char *input_line, char *output_token){
    char *temp;

    // Comportamento do scanset definido:
    // %*[ \t] ignora espaços e tabs que antecedem o token;
    // %[^ \t] lê o restante da linha, para ao encontrar a primeira ocorrência de um espaço ou tab e salva a string lida em output_token (não separa tokens "," e "+" quando );
    sscanf(input_line, "%*[ \t]%[^ \t]", output_token);

    // Testa se o token possui uma vírgula e a separa caso precise
    if ( temp = strstr(output_token, ",") ){
        // Se a posição da vírgula estiver em output_token[0], "apaga" o resto do token.
        if (temp == output_token) *(temp+1) = '\0';
        // Senão "apaga" o resto do token, inclusive a vírgula.
        else *temp = '\0';
    }

    // Testa se o token possui um + e o separa caso precise
    else if ( temp = strstr(output_token, "+") ){
        // Se a posição do "+" estiver em output_token[0], "apaga" o resto do token.
        if (temp == output_token) *(temp+1) = '\0';
        // Senão "apaga" o resto do token, inclusive o "+".
        else *temp = '\0';
    }

    // Retorna a quantidade de caracteres de output_token (desconsiderando '\0')
    return ( strlen(output_token) - 1 );
}

void get_line_tokens(){
//TODO: Usar strstr pra obter posição do último token lido e somar seu tamanho para pegar próximo token
}
