#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pig.h"

/* ------- Pig Latin function -------

This function takes a word and converts it to Pig Latin by moving the first consonant (or consonant cluster) to the end of the word and adding "ay" to the end. 
If the word begins with a vowel, "way" is added to the end.
If the word begins with a Y, then it acts as a consonant, but if it follows consonants, then it acts as a vowel

Arguments: word - the word to be converted to Pig Latin

Returns: The word in Pig Latin

*/
char* pig(char* word) {
    int len = strlen(word);
    char* pig_word = (char*) malloc((len + 3) * sizeof(char));
    int j = 0;

    // Check if the first character is a vowel
    if (strchr("AEIOUaeiou", word[0]) != NULL) {
        strcpy(pig_word, word);
        strcat(pig_word, "way");
    } else {
        // Find the first vowel in the word
        int i = 0;
        while (word[i] != '\0') {
            // Check if the character is a vowel or Y (which can be a vowel if not the first letter)
            if( i == 0 && word[i] == 'y') {
                i++;
                continue;
            }
            if(strchr("AEIOUaeiouYy", word[i]) != NULL) {
                break;
            }
            i++;
        }
        // Move all the consonants before the vowel to the end
        strcpy(pig_word, &word[i]);
        strncat(pig_word, word, i);
        strcat(pig_word, "ay");
    }
    return pig_word;
}
