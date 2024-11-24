/*********************************************************************
 *
 * https://www.cs.duke.edu/courses/fall08/cps196.1/Pthreads/bitonic.c
 *
 *********************************************************************/
// TODO: paralelizar kkkkk
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h> // adicionado
#include <time.h> // adicionado
#include <sys/stat.h> // adicionado
#include <sys/types.h> // adicionado
#include <unistd.h> // adicionado

long int LENGTH; 

FILE *fin, *fout;

char *strings;
long int N;

unsigned long int powersOfTwo[] =
{1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,
  65536,131072,262144,524288,1048576,2097152,4194304,8388608,
  16777216,33554432,67108864,134217728,268435456,536870912,
  1073741824};

#define ASCENDING  1
#define DESCENDING 0

/** procedure generate_output_filename()
 eu que criei isso aqui pra gente automatizar o negocio
 a gente pega o nome do arquivo de entrada e cria um arquivo de saída com mesmo nome só que .out no final
 **/
void generate_output_filename(const char *input_file, char *output_file) {
  const char *output_dir = "../outputs/";
  const char *input_basename = strrchr(input_file, '/');
  input_basename = (input_basename != NULL) ? input_basename + 1 : input_file; // Obtém apenas o nome do arquivo

  snprintf(output_file, 255, "%s%s", output_dir, input_basename); // Prefixa o diretório de saída
  output_file[255] = '\0'; // Garante o término seguro

  char *dot = strrchr(output_file, '.');
  if (dot && strcmp(dot, ".in") == 0) {
    strcpy(dot, ".out"); // Substitui a extensão .in por .out
  } else {
    strcat(output_file, ".out"); // Adiciona .out caso não exista
  }
}

/** procedure determine_string_size()
 eu que criei isso aqui pra gente automatizar o negocio
 ao inves de ter um define LENGHT (que diz o tamanho da string do arquivo) como constante ou passar como argumento
 é mais facil a gente determinar o tamanho da string lendo a segunda linha do arquivo (q contem a primeira string a ser lida)
 só temos que garantir que os arquivos de entrada estao em formato correto
 **/
void determine_string_size() {
  char buffer[1024];
  
  // le a primeira linha fodase
  if (fgets(buffer, sizeof(buffer), fin) == NULL) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }
  // le a segunda linha que contem a primeira string
  if (fgets(buffer, sizeof(buffer), fin) == NULL) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }

  buffer[strcspn(buffer, "\n")] = '\0';

  LENGTH = strlen(buffer) + 1; // +1 para o \0 no final da string
  
  // reposiciona o ponteiro
  rewind(fin);
}

void openfiles(const char *input_file, const char *output_file) {
  fin = fopen(input_file, "r+");
  if (fin == NULL ) {
    perror("fopen fin");
    exit(EXIT_FAILURE);
  }
  fout = fopen(output_file, "w");
  if (fout == NULL ) {
    perror("fopen fout");
    exit(EXIT_FAILURE);
  }
}

void closefiles(void) {
  fclose(fin);
  fclose(fout);
}

/** procedure compare()
 The parameter dir indicates the sorting direction, ASCENDING
 or DESCENDING; if (a[i] > a[j]) agrees with the direction,
 then a[i] and a[j] are interchanged.
 **/
void compare(int i, int j, int dir) {
  if (dir==(strcmp(strings+i*LENGTH,strings+j*LENGTH) > 0)) {
    char t[LENGTH];
    strcpy(t, strings+i*LENGTH);
    strcpy(strings+i*LENGTH, strings+j*LENGTH);
    strcpy(strings+j*LENGTH, t);
  }
}

/** Procedure bitonicMerge()
 It recursively sorts a bitonic sequence in ascending order,
 if dir = ASCENDING, and in descending order otherwise.
 The sequence to be sorted starts at index position lo,
 the parameter cbt is the number of elements to be sorted.
 **/
void bitonicMerge(int lo, int cnt, int dir, int cnt_threshold) {
	if (cnt <= 1) return;

	int k = cnt/2;
	int i;

	#pragma omp parallel for
	for(i = lo; i < lo+k; i++)
		compare(i, i+k, dir);

	if (cnt > cnt_threshold) {
		#pragma omp task firstprivate(k, lo)
		bitonicMerge(lo, k, dir, cnt_threshold);
		#pragma omp task firstprivate(k, lo)
		bitonicMerge(lo+k, k, dir, cnt_threshold);
		#pragma omp taskwait
		return;
	} else {
		bitonicMerge(lo, k, dir, cnt_threshold);
		bitonicMerge(lo+k, k, dir, cnt_threshold);
	}
		
}

/** function recBitonicSort()
 first produces a bitonic sequence by recursively sorting
 its two halves in opposite sorting orders, and then
 calls bitonicMerge to make them in the same order
 **/
void recBitonicSort(int lo, int cnt, int dir, int cnt_threshold) {
	if (cnt <= 1) return;

	int k = cnt/2;

	if (cnt>cnt_threshold) {
		#pragma omp task firstprivate(lo, k)
		recBitonicSort(lo, k, ASCENDING, cnt_threshold);

		#pragma omp task firstprivate(lo, k)
		recBitonicSort(lo+k, k, DESCENDING, cnt_threshold);

		#pragma omp taskwait
		bitonicMerge(lo, cnt, dir, cnt_threshold);
	} else {
		recBitonicSort(lo, k, ASCENDING, cnt_threshold);
		recBitonicSort(lo+k, k, DESCENDING, cnt_threshold);
		bitonicMerge(lo, cnt, dir, cnt_threshold);
	}
}

/** function sort()
 Caller of recBitonicSort for sorting the entire array of length N
 in ASCENDING order
 **/
void BitonicSort(int cnt_threshold) {
	#pragma omp parallel
	{
		#pragma omp single
		recBitonicSort(0, N, ASCENDING, cnt_threshold);
	}
}

/** the main program **/ 
int main(int argc, char **argv) {
  if (argc != 4) {
    printf("Usage: %s <input_file> <num_threads> <cnt_threshold>\n", argv[0]);
    return EXIT_FAILURE;
  }
  const char *input_file = argv[1];
  int num_threads = atoi(argv[2]);
  int cnt_threshold = atoi(argv[3]);

  char output_file[256];
  generate_output_filename(input_file, output_file);

  long int i;

  openfiles(input_file, output_file);
  determine_string_size();
  // esse trecho aq de cima eu criei tb pra gente testar com diferentes arquivos de entrada e tals

  fscanf(fin, "%ld", &N);
  if(N > 1073741824 || powersOfTwo[(int)log2(N)] != N) {
    printf("%ld is not a valid number: power of 2 or less than 1073741824!\n", N);
    exit(EXIT_FAILURE);
  }

  strings = (char*) calloc(N, LENGTH);
  if (strings == NULL ) {
    perror("malloc strings");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < N; i++)
    fscanf(fin, "%s", strings + (i * LENGTH));

  clock_t start = clock();
  BitonicSort(cnt_threshold);
  clock_t end = clock();

  for (i = 0; i < N; i++)
    fprintf(fout, "%s\n", strings + (i * LENGTH));

  free(strings);
  closefiles();

  // esse trecho aq debaixo adicionei tb
  // ja que a gente vai rodar no pczao (pra gente nao terq ficar monkeying around procurando essas saidas)
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

  // Verifica se o diretório results existe, caso contrário, cria 
  struct stat st = {0};
  if (stat("./results", &st) == -1) {
      if (mkdir("./results", 0700) == -1) {
          perror("mkdir /results");
          exit(EXIT_FAILURE);
      }
  }
  
  // Cria nome do arquivo de resultado "{nome_do_input}-{numero_de_threads}threads.txt"
  char *input_file_name = strrchr(argv[1], '/');
  char result_file_name[128];
  sprintf(result_file_name, "./results%s", input_file_name);

  // Verifica se OpenMP está sendo empregado
  int openmp = 0;
  #ifdef _OPENMP
  openmp = 1;
  #endif

  // Caso já existe o arquivo de resultado, adiciona o tempo dessa nova run
  if(access(result_file_name, F_OK) == 0){
    FILE *arq = fopen(result_file_name, "a");
    if(openmp==1){
      fprintf(arq, "Paralelo - %s Threads - Time: %f seconds\n", argv[2], time_spent);
    }
    else{
      fprintf(arq, "Serial - %s Threads - Time: %f seconds\n", argv[2], time_spent);
    }
    fclose(arq); 
  }
  // Caso contrário cria o arquivo do zero
  else{
    FILE *arq = fopen(result_file_name, "w");
    
    fprintf(arq, "Input file: %s\n", input_file_name);
    fprintf(arq, "Array size: %ld\n", N);
    fprintf(arq, "String size: %ld\n", LENGTH-1);
    if(openmp==1){
      fprintf(arq, "Paralelo - %s Threads - Time: %f seconds\n", argv[2], time_spent);
    }
    else{
      fprintf(arq, "Serial - %s Threads - Time: %f seconds\n", argv[2], time_spent);
    }
    
    fclose(arq);
  }
  
  return EXIT_SUCCESS;
}

