////////////////////////////////////////////////////////////////
//           Trabalho 02 de Software Básico - 2/2017          //
//     Tradutor de Macro-Assembler da linguagem hipotética    //
// Desenvolvido por: Amanda Alina da Cruz Silva  13/0100153   //
//                   Arthur de Matos Beggs       12/0111098   //
////////////////////////////////////////////////////////////////
//                          Ligador                           //
////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tab
{
    char label[50];
    int valor;
    //struct tab *prox;
};

int main(int argc, char *argv[])
{
    
    int i,j,k,l,m; 
    int ndef[]= {0,0,0}, nuso[]= {0,0,0}, tamanhorealoc=0, nArq;
    char c, realocacao[3][250], codigo[3][250];
    struct tab def[3][250], uso[3][250];

    ///aquisicao dos dados do usuario (Arquivos)
    // Considerando que o ligador será executado separadamente
    
    if (argc == 5 || argc == 4){
        nArq=argc-2;
    } else {
        printf("Erro! Numero errado de argumentos. \n");
        exit(1);
    }

    ///carrega as tabelas dos arquivos
    FILE *p[3];
    for (i=0; i<nArq; i++) {
        printf("%s\n", argv[i+1]);
        p[i]=fopen(argv[i+1], "r");
        while((c=getc(p[i]))!='\n');
        while((c=getc(p[i]))!='\n') {       //tabela de uso[i]
            uso[i][nuso[i]].label[0] = c;
            j=1;
            while((c=getc(p[i]))!= ' ') {
                uso[i][nuso[i]].label[j] = c;
                j++;
            }
            uso[i][nuso[i]].label[j] = '\0';
            fscanf(p[i],"%d", &uso[i][nuso[i]].valor);
            c=getc(p[i]);
            nuso[i]++;
        }
        fscanf(p[i],"\n");
        while((c=getc(p[i]))!='\n');
        while((c=getc(p[i]))!='\n') {       //tabela de uso
            def[i][ndef[i]].label[0] = c;
            j=1;
            while((c=getc(p[i]))!= ' ') {
                def[i][ndef[i]].label[j] = c;
                j++;
            }
            fscanf(p[i],"%d", &def[i][ndef[i]].valor);
            c=getc(p[i]);
            ndef[i]++;
        }

        while((c=getc(p[i]))!='\n');
        fscanf(p[i],"%s\n\n",realocacao[i]);
        while((c=getc(p[i]))!='\n');
        tamanhorealoc = strlen(realocacao[i]);
        fscanf(p[i],"%[^\n]",codigo[i]);
        fclose(p[i]);
    }

    for (j=0; j<nArq; j++) {
        printf("\nTabela de DEF do %s:\n", argv[j+1]);
        for(i=0; i<ndef[j]; i++) {
            printf("%s \t %d\n",def[j][i].label,def[j][i].valor);
        }
        printf("\nTabela de USO do %s:\n", argv[j+1]);
        for(i=0; i<nuso[j]; i++) {
            printf("%s \t %d\n",uso[j][i].label,uso[j][i].valor);
        }

        printf("\nTabela de Realocacao do %s:\n%s\n", argv[j], realocacao[j]);
        printf("\nCodigo do %s:\n%s\n", argv[j], codigo[j]);
        printf("\n");
    }

    ///encontra erros de ligação - tabela de uso não bate com tabela de definicao

    ///descobre o tamanho de cada arquivo (fator de correçao)
    /*  Descobrindo o tamanho utilizando strtok para dividir o vetor "codigo" em N tokens de cada byte do código,
        e depois usar atoi em cada token para preencher o vetor "codigo_int"
    */

    char space[] = " ";
    char *byte;
    int codigo_int[3][250], tamCodigo[]= {0,0,0};

    for (i=0; i<nArq; i++) {
        byte = strtok(codigo[i], space);
        while(byte!=NULL) {
            codigo_int[i][tamCodigo[i]]=atoi(byte);
            tamCodigo[i]++;
            byte = strtok(NULL, space);
        }
        printf("\n");
    }

    ///corrige o fator nas outras tabelas
    int valCorrecao;
    for (i=1, valCorrecao=0; i<nArq; i++) {
        valCorrecao+=tamCodigo[i-1];
        for (j=0; j<ndef[i]; j++) {
            def[i][j].valor+=valCorrecao;
        }
    }

    ///gera tabela geral de instruções
    struct tab *defGeral;
    int tamTabGeral;

    for (i=0, tamTabGeral=0; i<nArq; i++)
        tamTabGeral+=ndef[i];

    defGeral = malloc(sizeof(struct tab)*(tamTabGeral));

    for (i=0, k=0; i<nArq; i++) {
        for (j=0; j<ndef[i]; j++, k++) {
            defGeral[k].valor=def[i][j].valor;
            strcpy(defGeral[k].label, def[i][j].label);
        }
    }

    ///remonta o codigo objeto em ordem a partir da tabela geral e a de realocação
    int e_uso=0;
    for (i=0; i<nArq; i++) {
        for (j=0; j<nuso[i]; j++){
            for (l=0; l<tamTabGeral; l++) {
                if (strcmp(defGeral[l].label, uso[i][j].label)==0) {
                    codigo_int[i][uso[i][j].valor]+=defGeral[l].valor;
                    realocacao[i][uso[i][j].valor]='0';
                    break;
                }
            }
        }
    }

     for (i=0; i<nArq; i++) {
        for (j=0; j<tamCodigo[i]; j++) {
            if (realocacao[i][j]=='1') {
                for (l=1, valCorrecao=0; l<=i; l++) {
                    valCorrecao+=tamCodigo[l-1];
                }
                codigo_int[i][j]+=valCorrecao;
            }
        }
    }

    FILE *arquivo_saida = fopen(argv[nArq+1], "w");
    for (i=0; i<nArq; i++) {
        for (j=0; j<tamCodigo[i]; j++){
            fprintf(arquivo_saida, "%d ", codigo_int[i][j]);
        }
    }
    fprintf(arquivo_saida, "\n");

    free(defGeral);
    fclose(arquivo_saida);

    system("PAUSE");
    return 0;
}
