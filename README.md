# Bitonic Sort

## Diretórios

### /bitonic_openmp
Diretório com a versão do código que estamos alterando para suporte a OpenMP.  
Para rodar o algoritmo:

```sh
$ make
$ ./bitonic ../data/<input_file> <num_threads> <valor_threshold>
```

### /bitonic_standart
Diretório com o código padrão escrito pelo Pretto com "standart" em vez de "standard" (Perdão Mr. Forgetted)

### /inputs
Diretório com os arquivos de entrada (*.in)

### /outputs
Diretório com os arquivos de saída (*.out) gerados pelo bitonic

### /results
TODO: mexer em bitonic.c pra guardar os logs qnd for rodar no pczao

## generate_inputs.py
Script para gerar arquivos de entrada baseados em parâmetros configuráveis.  
Para mais informações sobre os parâmetros:

```sh
$ python generate_inputs.py --help
```

## Significado das Variáveis do Bitonic

- **LENGTH**: Comprimento máximo de cada string lida do arquivo de entrada.
- **N**: Número de strings lidas do arquivo de entrada (deve ser uma potência de 2).

## Uso do script bash "run_tests.sh"
Recebe 3 argumentos: potência do tamanho de arquivo de teste
                     numero máximo de threads (potência de 2)
                     valor de threshold

Por exemplo, quero rodar arquivos de tamanho até 2048, com 16 threads e valor de threshold 100.
```sh
$ ./run_testes.sh 11 16 100 
```      
                  |  |  |
                  |  |  --> valor the threshold em 100 (vou ser honesto não faço ideia doq faz esse valor)
                  |  |
                  |  --> Variando número de threads em até 16: [1,2,4,8,16]
                  |
                  --> Variando arquivos de entrada até 2048 (2**11): [sd_128x7, sd_256x7, sd_512x7, sd_1024x7, sd_2048x7]