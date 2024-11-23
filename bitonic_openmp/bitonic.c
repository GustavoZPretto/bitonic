/*********************************************************************
 *
 * https://www.cs.duke.edu/courses/fall08/cps196.1/Pthreads/bitonic.c
 *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h> // adicionado
#include <time.h> // adicionado

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
  strncpy(output_file, input_file, 255);
  output_file[255] = '\0';
  char *dot = strrchr(output_file, '.');
  if (dot && strcmp(dot, ".in") == 0) {
    strcpy(dot, ".out");
  } else {
    strcat(output_file, ".out");
  }
}

// TODO: fix this
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

  LENGTH = strlen(buffer);
  
  // reposiciona o ponteiro
  rewind(fin);
}

void openfiles(const char *input_file, const char *output_file) {
  printf("input_file: %s\n", input_file);
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
void bitonicMerge(int lo, int cnt, int dir) {
  if (cnt>1) {
    int k=cnt/2;
    int i;
    for (i=lo; i<lo+k; i++)
      compare(i, i+k, dir);
    bitonicMerge(lo, k, dir);
    bitonicMerge(lo+k, k, dir);
  }
}

/** function recBitonicSort()
 first produces a bitonic sequence by recursively sorting
 its two halves in opposite sorting orders, and then
 calls bitonicMerge to make them in the same order
 **/
void recBitonicSort(int lo, int cnt, int dir) {
  if (cnt>1) {
    int k=cnt/2;
    recBitonicSort(lo, k, ASCENDING);
    recBitonicSort(lo+k, k, DESCENDING);
    bitonicMerge(lo, cnt, dir);
  }
}

/** function sort()
 Caller of recBitonicSort for sorting the entire array of length N
 in ASCENDING order
 **/
void BitonicSort() {
  recBitonicSort(0, N, ASCENDING);
}

/** the main program **/ 
int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <input_file> <num_threads>\n", argv[0]);
    return EXIT_FAILURE;
  }
  const char *input_file = argv[1];
  int num_threads = atoi(argv[2]);
  
  char output_file[256];
  generate_output_filename(input_file, output_file);

  long int i;

  openfiles(input_file, output_file);
  determine_string_size();
  // esse trecho aq de cima eu criei tb pra gente testar com diferentes arquivos de entrada e tals

  fscanf(fin, "%ld", &N);
  printf("N: %ld\n", N);
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
  BitonicSort();
  clock_t end = clock();

  for (i = 0; i < N; i++)
    fprintf(fout, "%s\n", strings + (i * LENGTH));

  free(strings);
  closefiles();

  // esse trecho aq debaixo adicionei tb
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Number of threads: %d\n", num_threads);
  printf("Array size: %ld\n", N);
  printf("Input file: %s\n", input_file);
  printf("Time: %f seconds\n", time_spent);
  return EXIT_SUCCESS;
}

