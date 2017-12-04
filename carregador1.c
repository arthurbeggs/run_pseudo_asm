#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORDS 4

int main(int argc, char *argv[]){
  FILE *arq;
  int qnt_words;
  int i,j, inst, input, ACC, PC;
  int *v;
  

  // Abre um arquivo arquivo para leitura
  arq =fopen(argv[1], "rt");
  if (arq == NULL){
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
        j = v[i+1];
        a = v[j];
        ACC = ACC + a;
        i++;
      break;

      case 2 :
        printf("SUB\n");
        j = v[i+1];
        a = v[j];
        ACC = ACC - a;
        i++;
      break;

      case 3 :
        printf("MULT\n");
        j = v[i+1];
        a = v[j];
        ACC = ACC * a;
        i++;
      break;

      case 4 :
        printf("DIV\n");
        j = v[i+1];
        a = v[j];
        ACC = ACC / a;
        i++;
      break;

      case 5 :
        printf("JMP\n"); 
        PC = v[i+1];
        i = PC;
      break;

      case 6 :
        printf("JMPN\n");
        if (ACC<0){
          PC = v[i+1];
          i = PC;
        }
      break;

      case 7 :
        printf("JMPP\n");
        if (ACC>0){
          PC = v[i+1];
          i = PC;
        }
      break;

      case 8 :
        printf("JMPZ\n");
        if (ACC=0){
          PC = v[i+1];
          i = PC;
        }
      break;

      case 9 :
        printf("COPY\n");
        v[i+1] = v[i+2];
        i = i + 2; // copy tem dois operandos
      break;

      case 10 :
        printf("LOAD\n");
        ACC = v[i+1];
        i++;
      break;

      case 11 :
        printf("STORE\n");
        v[i+1] = ACC;
        i++;
      break;

      case 12 :
        printf("INPUT\n");
        scanf("%d", &input;
        v[i+1] = input;
        i++;
      break;

      case 13 :
        printf("OUTPUT\n");
        printf("%d\n", v[i+1] );
        i++;      
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

