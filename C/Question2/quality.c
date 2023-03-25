#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "riffle.h"

int main() {
    // Average quality for N 1 to 15 
    int shuffles = 15;
    int trials = 30;
    int N;
    printf("N\tAverage Quality\n");
    for (N = 1; N <= shuffles; N++) {
        float avg_q = average_quality(50, N, trials);
        printf("%d\t%.4f\n", N, avg_q);
    }
    return 0;
}


