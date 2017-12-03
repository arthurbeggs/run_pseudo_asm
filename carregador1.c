#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORDS 4

int main(int argc, char *argv[])
{
  FILE *arq;
  int qnt_words;
  int i, inst;
  int *v;
  char h, c, dois;

  // Abre um arquivo arquivo para leitura
  arq =fopen(argv[1], "rt");
  if (arq == NULL)  // Se houve erro na abertura
  {
     printf("Não foi possível abrir o arquivo \n");
     exit(1);
  }


  /// Preparação da Simulação
  //Pega a quatidade de words da segunda linha do arquivo
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


///SIMULAÇÂO

 for (int i = 0; i < qnt_words; ++i)
  {
    inst = v[i];
    switch ( inst )
    {
      case 1 :
        printf("ADD\n");
      break;

      case 2 :
        printf("SUB\n");
      break;

      case 3 :
        printf("MULT\n");
      break;

      case 4 :
        printf("DIV\n");
      break;

      case 5 :
        printf("JMP\n");
      break;

      case 6 :
        printf("JMPN\n");
      break;

      case 7 :
        printf("JMPP\n");
      break;

      case 8 :
        printf("JMPZ\n");
      break;

      case 9 :
        printf("COPY\n");
      break;

      case 10 :
        printf("LOAD\n");
      break;

      case 11 :
        printf("STORE\n");
      break;

      case 12 :
        printf("INPUT\n");
      break;

      case 13 :
        printf("OUTPUT\n");
      break;

      case 14 :
        printf("STOP\n");
      break;

        


    }

  } 






  fclose(arq);
  free(v);
  system("PAUSE");
  return 0;
    
}
