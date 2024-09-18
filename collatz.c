#include <stdio.h>
#include <stdlib.h>

unsigned long long int collatz_steps(unsigned long long int n) {
    unsigned long long int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else if (n % 2 == 1) {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

unsigned long long int Randomnizer(unsigned long long int MAX, unsigned long long int MIN) {
    unsigned long long int rand_num = rand() % (MAX - MIN + 1) + MIN;
    
    return rand_num;

}

int main(int argc, char *argv[]) {


return 0;

}