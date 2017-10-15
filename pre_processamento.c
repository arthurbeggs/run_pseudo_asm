////////////////////////////////////////////////////////////////
//           Trabalho 01 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
//   Preprocessamento: Somente avalia as diretivas EQU e IF.  //
////////////////////////////////////////////////////////////////

int pre_processamento (char *source, char *out){

    FILE *sfp; // Arquivo de entrada - source file pointer
    sfp = fopen (source,"r"); // Abre o arquivo de entrada e o lê para ser escrito no de saída.

    FILE *ofp; // Arquivo de saída - output file pointer
    ofp = fopen (out, "w"); // Cria o arquivo de saída com o nome dado pelo usuário. Será modificado posteriormente.

    if (sfp==NULL)
        printf("\n Houve um erro ao abrir o arquivo .asm! \n");
        exit(0);
    else {
        while (sfp!=NULL){
            fscanf (sfp,"Some String\n", &var); //LINHA ERRADA: deve ler o arquivo de entrada
            fwrite (ofp,"Some String\n", &var2); //LINHA ERRADA2: deve escrever o arquivo de entrada para a de saida
        }
    }
    fclose (sfp);
    fclose (ofp);

    ofp = fopen (out, "r+"); // Abre o arquivo de saída para leitura e modificação

    // código de pre processamento

    fclose (ofp);
}
