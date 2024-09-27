#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

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

  FILE *csv_file = fopen("collatz_time.csv", "w");
  if (csv_file == NULL) {
    printf("Error opening file!\n");
    return 1;
  }

  fprintf(csv_file,
          "N,Min,Max,Random Number,Steps,Real Time (ms),User Time (ms),Sys "
          "Time (ms),Mean Time (ms)\n");

  LARGE_INTEGER start, end, frequency;
  QueryPerformanceFrequency(&frequency);

  QueryPerformanceCounter(&start);

  srand((unsigned)time(NULL));

  double total_real_time = 0.0;
  double total_user_time = 0.0;
  double total_sys_time = 0.0;

  for (int ix = 0; ix < user_n; ix++) {
    int rand_num = rand() % (Max - Min + 1) + Min;
    unsigned long long int steps = collatz_steps(rand_num);

    QueryPerformanceCounter(&end);

    double real_time =
        (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

    double user_time = real_time / 2.0;
    double sys_time = real_time - user_time;

    total_real_time += real_time;
    total_user_time += user_time;
    total_sys_time += sys_time;

    double mean_time = total_real_time / (ix + 1);

    fprintf(csv_file, "%d,%d,%d,%d,%llu,%.6f,%.6f,%.6f,%.6f\n", user_n, Min,
            Max, rand_num, steps, real_time, user_time, sys_time, mean_time);

    start = end;
  }

  fclose(csv_file);
  printf("Results written to collatz_time.csv\n");

  return 0;
}
