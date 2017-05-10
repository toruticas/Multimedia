# Intodução

Este programa tem como objetivo comprimir um arquivo de imagem usando o algorítimo LZW. Todas as definições da especificação pode ser encontrado dentro do arquivo **especification.pdf**.

# Colaboradores

NOME: Rafael Mariano de Castro Silva - #USP: 7564023

# Definições

A compressão foi feita usando-se trechos de código do arquivo de leitura da imagem(parse.c) oferecido junto com a especificação do projeto. Os arquivos que foram oferecidos com a especificação podem ser encontrados dentro do único arquivo zip desta aplicação.

## Codificação

No processo de códificação, cada cor foi representada por um ```unsigned char``` pois estes tem o arranjo de **0-255** que, por sua vez, possuem o tamanho de 1 byte. Cada palavra é definida por um array de ```unsigned char``` em uma struct, chamada ```TWord```, que é responsável por respresentar cada palavra.

Estas palavras são salvas uma estrutura de complexidade **O(log(n))**, a **Trie**, para que tanto a inserção como a busca por palavras tenha a complexidade algorítimica supracitada. Esta estrutura foi escolhida pois não há custo para remoção e atualização de palavras, uma vez que estas operações não ocorrem no processo de codificação.

O pseudo código, mostrado abaixo, foi retirado da referência sobre o algorítmo LZW.

```
word s
character ch
...

s = empty word;
while (there is still data to be read) {
  ch = read a character;
  if (dictionary contains s+ch) {
    s = s + ch
  } else {
    encode s to output file
    add s + ch to dictionary
    s = ch
  }
}
encode s to output file;
```

## Decodificação

Não foi implementado.

# Execução

Para o desenvolvimento do projeto foi usado a versão "g++ (GCC) 6.3.1 20170306" do compilador. Além disso, não é usado nenhuma lib externa ou que dependa de um sistema operacional específico

## Codificação

Para compilar o programa basta rodar o comando no terminal:

```
g++ -o encode parse.cpp bitmap.cpp encode.cpp trie.cpp -lm
```

Para executar o comando basta executar o comando no terminal:

```
./encode -i bmps/01.bmp -o bins/01.bin -n 10
```

## Decodificação

Não foi implementado.

# Referências

https://www.cs.duke.edu/csed/curious/compression/lzw.html
http://www.geeksforgeeks.org/trie-insert-and-search/
https://www.topcoder.com/community/data-science/data-science-tutorials/using-tries/
https://threads-iiith.quora.com/Tutorial-on-Trie-and-example-problems
