## **Montador, Ligador e Carregador de Pseudo-Assembly**

**Compilado com** gcc 6.3.0 20170406 (Ubuntu 6.3.0-12ubuntu2)

***

### **Instruções de Compilação:**


***

### **Montador:**

```bash
> ./assembler <source_file> ...
```


Recebe de 1 a 3 arquivos `.asm` e gera um arquivo objeto `.o` para cada arquivo de entrada com cabeçalho no padrão a seguir:

```
H: NOME_DO_PROGRAMA
H: TAMANHO_EM BYTES
H: MAPA_DE_BITS
TU: TABELA_DE_USO (opcional)
TD: TABELA_DE_DEFINIÇÕES (opcional)
T: CÓDIGO_MÁQUINA
```

`NOME_DO_PROGRAMA` : Mesmo nome do arquivo fonte (sem o `.asm`);

`TAMANHO_EM_BYTES` : Bytes do código-máquina;

`MAPA_DE_BITS` : Cada caracter representa uma *word* (16 bits) do código-máquina. Se 0, o endereço é absoluto. Se 1, o endereço é relativo;

`TABELA_DE_USO` : Se o arquivo for dividido em módulos, as informações da tabela de usos aparecem aqui;

`TABELA_DE_DEFINIÇÕES` : Se o arquivo for dividido em módulos, as informações da tabela de definições aparecem aqui;

`CÓDIGO_MÁQUINA` : Cada *word* (16 bits) é representada por um número de 2 dígitos em representação decimal. As *words* são separadas por espaços e não há quebra de linha.


### **Ligador:**

```
> ./linker <object_file> ...
```

Recebe de 1 a 3 arquivos `.o` e gera um arquivo executável sem extensão com nome de saída igual ao nome do primeiro arquivo objeto fornecido.

Os arquivos são ligados na ordem dos argumentos passados.

O arquivo executável possui a seguinte estrutura:
```
H: NOME_DO_PROGRAMA
H: TAMANHO_EM BYTES
H: MAPA_DE_BITS
T: CÓDIGO_MÁQUINA
```

`NOME_DO_PROGRAMA` : Mesmo nome do primeiro arquivo objeto (sem o `.o`);

`TAMANHO_EM_BYTES` : Bytes do código-máquina;

`MAPA_DE_BITS` : Cada caracter representa uma word (16 bits) do código-máquina. Se 0, o endereço é absoluto. Se 1, o endereço é relativo;

`CÓDIGO_MÁQUINA` : Cada *word* (16 bits) é representada por um número de 2 dígitos em representação decimal. As *words* são separadas por espaços e não há quebra de linha.


### **Carregador:**

```bash
> ./loader <executable_file> <chunks> <chunk_size> ... <chunk_address> ...
```

Recebe como argumentos:
- Um arquivo executável `<executable_file>`;
- O número de *chunks* de memória `<chunks>`;
- Um argumento `<chunk_size>` para cada *chunk* contendo seu tamanho em bytes;
- Um argumento `<chunk_address>` para cada *chunk* contendo o endereço de memória inicial do chunk.

Gera um arquivo de extensão `.im` com a imagem de memória do programa carregado.

O carregador simula o programa executável e então tenta carregá-lo em um *chunk*. Caso nenhum *chunk* possua tamanho suficiente para o carregamento do executável, o carregador tenta dividir o executável entre os *chunks*. Se ainda não for possível carregar o programa, uma mensagem de *"OUT OF MEMORY"* é gerada e o carregador aborta a execução sem gerar o arquivo de saída `.im`.


***

### **Especificações completas:**

As especificações completas se encontram na pasta **specs**, sendo o arquivo `trabalho2.pdf` a especificação desse trabalho, que é complementar ao trabalho anterior, `trabalho1.pdf`.
