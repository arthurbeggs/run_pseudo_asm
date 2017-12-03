#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  FILE *arq;
  int qnt_words;
  int i, a =1;
  char h, c, dois;
  // Abre um arquivo arquivo para leitura
  arq =fopen(argv[1], "rt");
  if (arq == NULL)  // Se houve erro na abertura
  {
     printf("Não foi possível abrir o arquivo \n");
     exit(1);
  }
  /// Pega a quatidade de words da segunda linha do arquivo
   while((c=getc(arq))!='\n'); 
   while(((c=getc(arq))!='H') ||((c=getc(arq))!=':') || ((c=getc(arq))!=' '));
   fscanf(arq, "%d", &qnt_words); 
   //printf("O qnt_words é: %d\n", qnt_words);

  fclose(arq);

  system("PAUSE");
  return 0;
    
}
