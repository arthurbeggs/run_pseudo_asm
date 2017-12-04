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
  int i,j, inst, input, ACC, PC, a, v[26];
  //int *v;
  //char *r;
  char c, r[26];
  

  // Abre um arquivo arquivo para leitura
  arq =fopen(argv[1], "r");
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


  /
  v =(int *) malloc(qnt_words * WORDS); //Alocar um vetor com o TAMANHO
   if(v == NULL)
  {
    printf("Nao possivel alocar memoria\n");
    return 1;
  }
  r = (char *) malloc((qnt_words+1)*sizeof(char));
  if(r == NULL)
  {
    printf("Nao possivel alocar memoria\n");
    return 1;
  }
  
  //while((c=getc(arq))!='\n'); // pula pra quarta linha
  i = 0;
  getc(arq);
  getc(arq);
  getc(arq);
  getc(arq);
  getc(arq);
  printf("Realoc:\n");
  do
  {
    fscanf(arq, "%c", &r[i]);
    printf("%c\n", r[i]);
    i++;
  }while(i<qnt_words);

  i = 0;
  getc(arq);
  getc(arq);
  getc(arq);
  getc(arq);
  getc(arq);
  printf("words:\n");
  do
  {
    fscanf(arq, "%d", &v[i]);
    printf("%d\n", v[i]);
    i++;
  }while(i<qnt_words);
  
  
///SIMULAÇÂO

 for (int i = 0; i < qnt_words; ++i)
  {
    inst = v[i];
    PC = i;
    if( ( (r[i] = 0) && (r[i+1] != 0)  ) || ( (v[i] = 14) && (r[i-1] = 1) ) )
    {

      switch ( inst )
      {
        case 0 :
        printf("SPACE\n");
        break;

        case 1 :
          printf("ADD\n");
          j = v[i+1];
          a = v[j];
          ACC = ACC + a;

        break;

        case 2 :
          printf("SUB\n");
          j = v[i+1];
          a = v[j];
          ACC = ACC - a;
          
        break;

        case 3 :
          printf("MULT\n");
          j = v[i+1];
          a = v[j];
          ACC = ACC * a;
          
        break;

        case 4 :
          printf("DIV\n");
          j = v[i+1];
          a = v[j];
          ACC = ACC / a;
          
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
          
        break;

        case 10 :
          printf("LOAD\n");
          ACC = v[i+1];
          
        break;

        case 11 :
          printf("STORE\n");
          v[i+1] = ACC;
          
        break;

        case 12 :
          printf("INPUT\n");
          scanf("%d", &input);
          v[i+1] = input;
          
        break;

        case 13 :
          printf("OUTPUT\n");
          printf("%d\n", v[i+1] );
                
        break;

        case 14 :
          printf("STOP\n");
          break;
      }
    }  
  }

printf("ACC = %d\n", ACC);
printf("PC =%d\n", PC);
  



  fclose(arq);
  free(v);
  free(r);
  system("PAUSE");
  return 0;
    
}

