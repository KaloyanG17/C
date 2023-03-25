#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "beggar.h"

/* -------- Statistics Function --------

This functions calculates the shortest and longest game, and the average number of turns for a given number of players from a given number of games.

Arguments:Nplayers - number of players
          games - number of games to be played

Returns: An array of 3 integers, where the first element is the shortest game, the second element is the longest game, and the third element is the average number of turns.
*/
int *statistics(int Nplayers, int games){
    // Create array to store statistics
    int *stats = malloc(3 * sizeof(int));
    // Create array to store number of turns for each game
    int *turns = malloc(games * sizeof(int));
    // Create array to store deck
    int deck[52] = {2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14};
    // Create variables to store shortest, longest, and total number of turns
    int shortest = 1000;
    int longest = 0;
    int total = 0;
    // Play games
    int i;
    for (i = 0; i < games; i++){
        // Store number of turns for each game
        turns[i] = beggar(Nplayers, deck, 0);

        // Check if its the shortest
        if (turns[i] < shortest){
            shortest = turns[i];
        }
        // Check if its the longest
        if (turns[i] > longest){
            longest = turns[i];
        }

        // Update total number of turns
        total += turns[i];
    }
    // Calculate average number of turns
    int average = total / games;
    // Store statistics in array
    stats[0] = shortest;
    stats[1] = longest;
    stats[2] = average;

    free(turns);
    // Return array of statistics
    return stats;
}


int main() {
    // Number of players and number of trials
    int Nplayers = 0;
    int trials = 0;

    // Terminal prompt for how many players
    printf("How many players? ");
    // Check if input is valid
    while(Nplayers < 2){
        scanf("%d", &Nplayers);
        if (Nplayers > 1){
            break;
        }
        printf("Please enter a number greater than 1: ");
    }

    // Terminal prompt for number of trials (Can glitch if you enter input too fast on VM but should work fine on a local machine)
    printf("How many trials? ");
    // Check if input is valid
    while(trials < 1){
        scanf("%d", &trials);
        if (trials > 0){
            break;
        }
        printf("Please enter a number greater than 0: ");
    }

    // Get statistics
    int *stats = statistics(Nplayers, trials);

    // Print statistics in a nice format
    printf("\n------------ %d Player Statistics in %d Trials ------------ \n", Nplayers, trials);
    printf("-Shortest game: %d \n", stats[0]);
    printf("-Longest game: %d \n", stats[1]);
    printf("-Average number of turns: %d \n", stats[2]);
    printf("------------------------------------------------------------ \n\n");

    free(stats);
    

    return 0;
}