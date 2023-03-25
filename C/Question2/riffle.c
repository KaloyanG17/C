#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "riffle.h"

/*  ------- Riffle Once function -------

This functions takes an array and shuffles it once. It does this by splitting it in half and randomly choosing a side 
and adding the top of that half to the work array. It does this until both halfs are empty.

Arguments: L - Array
           len - length of the array
           size - size of each element in the array
           work - array to store the shuffled array
           
Returns: Shuffled once array
*/
void riffle_once(void *L, int len, int size, void *work)  {
    // work pointer to set values in work array
    char* work_ptr = work;

    // Setting pointers to the start and end of the array
    char* start = (char*) L;
    char* end = start + ((len - 1) * size);
    char* last = end;
    
    // Find the centre point of the list 
    int centre = len / 2;
    // Setting left and right pointers of the 2 halfs
    char* left = start;
    char* right = start + (centre * size);
    int flagEnd = 0;

    srand(time(NULL));
    while(1) {
        // If the left or right poitner is at the end, add the last element to the work array
        if (right == end) {
            if (flagEnd == 0) {
                memcpy(work_ptr, last, size);
                flagEnd = 1;
                work_ptr += size;
            } else {
                if (left == start + (centre * size)) {
                    break;
                }
                memcpy(work_ptr, left, size);
                work_ptr += size;
                left += size;
            }
        }
        // If the left pointer is at the centre and the right pointer is at the end, break
        if(left == start + (centre * size) && right == end && flagEnd == 1){
            break;
        }
        // Randomly choose a element from the left or right half 
        int random = rand() % 2;

        if(random % 2 == 0){  
            // If the left pointer is at the centre point, add from the right
            if(left == start + (centre * size)){
                memcpy(work_ptr, right, size);
                work_ptr += size;
                right += size;
            } else {
                // Otherwise add from the left
                memcpy(work_ptr, left, size);
                work_ptr += size;
                left += size;
            }
        } else {
            // If the right pointer is at the end, add from the left
            if (right == end) {
                memcpy(work_ptr, left, size);
                work_ptr += size;
                left += size; 
            } else {
            // Otherwise add from the right
                memcpy(work_ptr, right, size);
                work_ptr += size;
                right += size;
            }
        }
    }
    // Copy the work array to the original array
    memcpy(L, work, len * size);
}

/*  ------- Riffle function -------

This functions takes an array and shuffles it N times. 
It does this by calling the riffle_once function N times.

Arguments: L - Array
           len - length of the array
           size - size of each element in the array
           N - number of times to shuffle

Returns: Shuffled array N times
*/
void riffle(void *L, int len, int size, int N) {
    // Allocate memory for the work array
    int* work2 = malloc(len * size);
    // Call the riffle_once function N times
    int i, j;
    for (i = 0; i < N; i++) {
        riffle_once(L, len, size, work2);
    }
    // Free the work array memory
    free(work2);
}

/*  ------- cmp_int function -------

This function checks if the original array is in the shuffled array by comparing each integer in the original array to each element in the shuffled array.

Arguments: a - Array of Integers
           b - Array of Integers

Returns: 1 if the arrays are the same, 0 if they are not
*/
int cmp_int(void *a, void *b) {
    // Cast the void pointers to int pointers
    int *ia = (int *) a;
    int *ib = (int *) b;
    // Compare the values of the int pointers, returning -1 if its invalid
    if (*ia < *ib) return -1;
    else if (*ia > *ib) return 1;
    // If the values are the same, return 0
    else return 0;
}

/*  ------- cmp_str function -------

This function checks if the original array is in the shuffled array by comparing each string in the original array to each element in the shuffled array.

Arguments: a - Array of Strings
           b - Array of Strings

Returns: 1 if the arrays are the same, 0 if they are not
*/
int cmp_str(void *a, void *b) {
    // Cast the void pointers to char pointers
    char **sa = (char **) a;
    char **sb = (char **) b;
    // Compare the values of the char pointers, returning -1 if its invalid
    return strcmp(*sa, *sb);
}

/* ------- Check shuffle function -------

This function checks if the original array is in the shuffled array by comparing each element in the original array to each element in the shuffled array.

Arguments: L - Array
           len - length of the array
           size - size of each element in the array
           cmp - function to compare the elements in the array

Returns: 1 if the arrays are the same, 0 if they are not
*/
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *)) {
    int i, j;
    // Compare each element in the original array to each element in the shuffled array by calling the cmp function for which type of array it is
    for (i = 0; i < len; i++) {
        for (j = 0; j < len; j++) {
            if (cmp(L + i * size, L + j * size) == 0) {
                break;
            }
        }
        // If the element is not in the shuffled array, return 0
        if (j == len) {
            return 0;
        }
    }
    // If all the elements are in the shuffled array, return 1
    return 1;
}

/* ------- Quality function -------

This function calculates the quality of the shuffle by counting the number of integers that are in order in each pair of integers in the shuffled array.
Then it divides this number by the number of integers in the array.

Arguments: numbers - Array of Integers
           len - length of the array

Returns: The quality of the shuffle as a float
*/
float quality(int *numbers, int len) {
    // Count the number of elements that are in order
    int count = 0;
    int i;
    for (i = 0; i < len - 1; i++) {
        if (numbers[i] < numbers[i+1]) {
            count++;
        }
    }
    // Calculate the quality of the shuffle as a float
    float quality = (float) count / (len - 1);
    return quality;
}

/* ------- Average quality function -------

This function calculates the average quality of the shuffle by calling the quality function N times and dividing the sum of the qualities by the number of times it was called.

Arguments: N - length of the array
           shuffles - number of times to shuffle
           trials - number of times to call the quality function

Returns: The average quality of the shuffle as a float
*/
float average_quality(int N, int shuffles, int trials) {
    int i, j;
    float sum = 0;
    // Allocate memory for the array of integers
    for (i = 0; i < trials; i++) {
        int *numbers = malloc(N * sizeof(int));
        // Fill the array with the numbers 1 to N
        for (j = 0; j < N; j++) {
            numbers[j] = j;
        }
        // Shuffle the array N times
        riffle(numbers, N, sizeof(int), shuffles);
        // Calculate the quality of the shuffle
        sum += quality(numbers, N);
        free(numbers);
    }
    // Calculate the average quality of the shuffle
    float average = sum / trials;
    return average;
}
