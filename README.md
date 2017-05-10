# Observações
* Cada valor RGB é representado por 1 byte (0~255) padrão RG

# Compilar

```
g++ -o encode parse.cpp encode.cpp trie.cpp -lm
```

# Desenvolviment

```
g++ -o encode parse.cpp encode.cpp trie.cpp -lm && ./encode -i bmps/02.bmp -o bins/teste2.bin -n 20
```
