#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long int collatz_steps(unsigned long long int n) {
  unsigned long long int steps = 0;
  while (n != 1) {
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = 3 * n + 1;
    }
    steps++;
  }
  return steps;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: %s <num_values> <min_value> <max_value>\n", argv[0]);
    return 1;
  }

  int user_n = atoi(argv[1]);
  int Min = atoi(argv[2]);
  int Max = atoi(argv[3]);

  FILE *csv_file = fopen("collatz_results.csv", "w");
  if (csv_file == NULL) {
    printf("Error opening file!\n");
    return 1;
  }

  fprintf(csv_file, "N,Min,Max,Random Number,Steps\n");

  srand(time(NULL));

  for (int ix = 0; ix < user_n; ix++) {
    int rand_num = rand() % (Max - Min + 1) + Min;
    unsigned long long int steps = collatz_steps(rand_num);

    fprintf(csv_file, "%d,%d,%d,%d,%llu\n", user_n, Min, Max, rand_num, steps);
  }

  fclose(csv_file);

  printf("Results written to collatz_results.csv\n");

  return 0;
}
