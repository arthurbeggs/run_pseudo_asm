#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORDS 4

int main(int argc, char *argv[])
{
  FILE *arq;
  int qnt_words, xuxu;
  int i, vet[4];
  int *v;
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

  v =(int *) malloc(qnt_words * WORDS); //Alocar um vetor com o TAMANHO

  
  while((c=getc(arq))!='\n'); // pula pra quarta linha
  while(((c=getc(arq))!='T') ||((c=getc(arq))!=':') || ((c=getc(arq))!=' '));
  i=0;
  do{ //salva as words no vetor alocado
    fscanf(arq, "%d", &v[i] );
    i++; 
      
  }while ((c=getc(arq))!= '\n');
  

 /*for (int i = 0; i < qnt_words; ++i)  {
       printf("%d\n", v[i]);
 }*/


///SIMULAÇÂO...






  fclose(arq);
  free(v);
  system("PAUSE");
  return 0;
    
}
