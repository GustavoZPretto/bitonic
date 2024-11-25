# Bitonic Sort

## Diretórios

### /bitonic_openmp
Diretório com a versão do código que estamos alterando para suporte a OpenMP.  
Para rodar o algoritmo:

```sh
$ make
$ ./bitonic ../data/<input_file> <num_threads> <valor_threshold>
```
#### /results
Contém os resultados das runs

### /bitonic_standart
Diretório com o código padrão escrito pelo Pretto com "standart" em vez de "standard" (Perdão Mr. Forgetted)

### /inputs
Diretório com os arquivos de entrada (*.in)
Como os arquivos são grandes, estamos armazenando com git lfs. Para baixa-los
sudo apt install git-lfs
```sh
$ sudo apt install git-lfs
$ git lfs install
$ git lfs pull
```


### /outputs
Diretório com os arquivos de saída (*.out) gerados pelo bitonic

## generate_inputs.py
Script para gerar arquivos de entrada baseados em parâmetros configuráveis.  
Para mais informações sobre os parâmetros:

## graphics.ipynb
Gera os gráficos utilizando os arquivos de resultados em bitonic_openmp/results e salva na pasta graphics

```sh
$ python generate_inputs.py --help
```

## Significado das Variáveis do Bitonic

- **LENGTH**: Comprimento máximo de cada string lida do arquivo de entrada.
- **N**: Número de strings lidas do arquivo de entrada (deve ser uma potência de 2).

## Uso do script bash "run_tests.sh"
Recebe 3 argumentos: potência do tamanho de arquivo de teste
                     numero máximo de threads
                     valor de threshold

Por exemplo, quero rodar arquivos de tamanho até 2048, com até 8 threads e valor de threshold 100.
```sh
$ ./run_testes.sh 11 16 100 
```      
                  |  |  |
                  |  |  --> valor the threshold em 10000 (valor utilizado nos testes)
                  |  |
                  |  --> Variando número de threads em até 8: [1,2,4,6,8]
                  |
                  --> Variando arquivos de entrada até 2048 (2**11): [sd_128x7, sd_256x7, sd_512x7, sd_1024x7, sd_2048x7]