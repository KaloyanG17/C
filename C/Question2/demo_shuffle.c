#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "riffle.h"

int main() {
    // Array of numbers
    int nums[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int *nums_copy = malloc(20 * sizeof(int));
    int i;

    // Shuffle nums array
    riffle_once(nums, 20, sizeof(int), nums_copy);
    printf("Shuffled nums array: ");
    for (i = 0; i < 20; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    // Check shuffle
    printf("Check shuffle: ");
    if (check_shuffle(nums, 20, sizeof(int), cmp_int)) {
        printf("Shuffle is correct\n");
    } else {
        printf("Shuffle is incorrect\n");
    }


    /* ------------------------- Greek Letter Section ------------------------- */

    // Greek array
    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu" };
    char **greek_copy = malloc(12 * sizeof(char *));

    // Shuffle Greek array
    riffle_once(greek, 12, sizeof(char *), greek_copy);
    printf("Shuffled greek array: ");
    for (i = 0; i < 12; i++) {
        printf("%s ", greek[i]);
    }
    printf("\n");

    // Check shuffle
    printf("Check shuffle: ");
    if (check_shuffle(greek, 12, sizeof(char *), cmp_str)) {
        printf("Shuffle is correct\n");
    } else {
        printf("Shuffle is incorrect\n");
    }

    // Free memory
    free(nums_copy);
    free(greek_copy);

    return 0;
}
