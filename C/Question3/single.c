#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "beggar.h"

int main() {
    int deck[52] = {2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14};
    
    // Terminal prompt for how many players
    int players = 0;
    int turns;
    printf("How many players? ");
    // Check if input is valid
    while(players < 2){
        scanf("%d", &players);
        if (players > 1){
            break;
        }
        printf("Please enter a number greater than 1: ");
    }

    // Get number of turns
    turns = beggar(players, deck, 0);
    // Print number of turns
    printf("Game finished in %d turns \n" , turns);
    return 0;
}