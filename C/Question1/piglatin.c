#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// include the header file for the pig function
#include "pig.h"

// Maximum line length 
#define MAX_LINE 1000

/*  ------- Pig Latin function -------

This function repeatedly prompts the user for a line of English text and prints the line in Pig Latin.
This is stopped when the user enters an empty line.

Arguments: None - User input

Returns: The line in Pig Latin
*/
int main() {
    char line[MAX_LINE];

    // Loop until the user enters an empty line
    while (1) {
        printf("Enter a line of English: ");
        fgets(line, MAX_LINE, stdin);
        // Check if the user entered an empty line and break if so
        if (strlen(line) <= 1) {
            break;
        }
        // Tokenize the line
        char* token = strtok(line, " \n\t");

        // Loop through each token and translate to Pig Latin in the format "word" => "ordway"
        while (token != NULL) {
            char* pig_word = pig(token);
            printf("%s => %s \n", token, pig_word);
            free(pig_word);
            token = strtok(NULL, " \n\t");
        }
        // Print a new line
        printf("\n");
    }
    return 0;
}




