# Bitonic Sort

## Diretórios

### /bitonic_openmp
Diretório com a versão do código que estamos alterando para suporte a OpenMP.  
Para rodar o algoritmo:

```sh
$ make
$ ./bitonic ../data/<input_file> <num_threads>
```

### /bitonic_standart
Diretório com o código padrão escrito pelo Pretto com "standart" em vez de "standard"

### /data
Diretório onde estão os arquivos de entrada e saída.

- **Arquivos de entrada (*.in)**: Contêm os arquivos input.
- **Arquivos de saída (*.out)**: Contêm os outputs gerados pelo programa.

## generate_inputs.py
Script para gerar arquivos de entrada baseados em parâmetros configuráveis.  
Para mais informações sobre os parâmetros:

```sh
$ python generate_inputs.py --help
```

## Significado das Variáveis do Bitonic

- **LENGTH**: Comprimento máximo de cada string lida do arquivo de entrada.
- **N**: Número de strings lidas do arquivo de entrada (deve ser uma potência de 2).