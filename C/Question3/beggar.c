#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "beggar.h"

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
    int i;
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

/* ------- Check shuffle function -------

This function checks if the original array is in the shuffled array by comparing each element in the original array to each element in the shuffled array.

Arguments: L - Array
           len - length of the array
           size - size of each element in the array

Returns: 1 if the arrays are the same, 0 if they are not
*/
int check_shuffle(void *L, int len, int size) {
    int i, j;
    // Compare each element in the original array to each element in the shuffled array by calling the cmp function for which type of array it is
    for (i = 0; i < len; i++) {
        for (j = 0; j < len; j++) {
            if (cmp_int(L + i * size, L + j * size) == 0) {
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

/* ------- Beggar function -------

This function plays the beggar card game with Nplayers. It deals a shuffled deck out to each player and then each player takes turns laying a card in the pile. 
If a player lays a card that is J(11), Q(12), K(13) or A(14) the next player must pay the penalty which is 1 , 2, 3 or 4 cards respectively.
The player who played the penalty card gets to take the pile and add it to their hand.
The game ends when a player has all the cards in the deck and the others have none.

Arguments: Nplayers - Number of players
           deck - Array of cards
           talkative - 0 if it shouldnt be printed, non-zero if it should be printed

Returns: Number of turns it took to finish the game
*/
int beggar(int Nplayers, int *deck, int talkative) {
    // Shuffle the array using the shuffle function from Question2 10 times
    riffle(deck, 52, sizeof(int), 10);
    
    // Check if the deck is shuffled correctly
    int check = check_shuffle(deck, 52, sizeof(int));
    if (check != 1) { 
        // Break if the deck isnt shuffled correctly
        printf("The deck is not shuffled correctly\n");
        return 0;
    }

    // Create variables for the turns, the player who is playing, the length of the pile, the card that was played and the penalty
    int turns = 0;
    int playing = 0;
    int lenPile = 52;
    int cardPlayed = 0;
    int won = 0;
    int i, j, k;
    
    // Create an array for the players and a length array for each player
    int players[Nplayers][52];
    int lenPlayers[Nplayers];

    // Set all the values in the players arrays to 0
    for (i = 0; i < Nplayers; i++) {
        for (j = 0; j < 52; j++) {
            players[i][j] = 0;
        }
    }
    for (i = 0; i < Nplayers; i++) {
        lenPlayers[i] = 0;
    }

    // Deal the cards to the players 

    for (i = 0; i < Nplayers; i++) {
        for (j = 0; j < 52/Nplayers ; j++) {
            players[i][j] = deck[i + (j * Nplayers)];
            lenPlayers[i]++;
            lenPile = lenPile - 1;
            deck[i + (j * Nplayers)] = 0;
        }
    }

    // Add the rest of the cards to the pile
    int pile[52];
    for (i = 0; i < 52; i++) {
        pile[i] = 0;
    }

    for (i = 0; i < 52; i++) {
        if (deck[i] != 0) {
            for (j = 0; j < 52; j++) {
                if (pile[j] == 0) {
                    pile[j] = deck[i];
                    break;
                }
            }
        }
    }

    // Set the first card played to the first card in the pile
    cardPlayed = pile[0];
  
    while(won != 1) {
        // Print the turn ,pile and everyones hand
        if (talkative) {
            printf("Turn %d", turns);
            // check if the pile is empty
            if (cardPlayed == 0) {
                printf("            Pile is empty so player %d should lay a single card" , playing);
            } else if (cardPlayed < 11) {
                printf("            Top card in the deck is %d , so Player %d should lay a single card", cardPlayed , playing);
            } else if (cardPlayed == 11) {
                printf("            Top card in the deck is 11 , so Player %d should lay 1 penalty card", playing);
            } else if (cardPlayed == 12) {
                printf("            Top card in the deck is 12 , so Player %d should lay 2 penalty cards ", playing);
            } else if (cardPlayed == 13) {
                printf("            Top card in the deck is 13 , so Player %d should lay 3 penalty cards ", playing);
            } else if (cardPlayed == 14) {
                printf("            Top card in the deck is 14 , so Player %d should lay 4 penalty cards ", playing);
            }

            printf("\n");
            printf("Pile: ");
            for (i = 0; i < lenPile ; i++) {
                printf("%d ", pile[i]);
            }
            printf("\n");
            for (i = 0; i < Nplayers; i++) {
                if (i == playing){  
                    printf("*   Player %d: ", i);
                } else {
                    printf("    Player %d: ", i);
                }
                j = 0;
                while(j < lenPlayers[i]){
                    printf("%d ", players[i][j]);
                    j++;
                }
                printf("\n");
            }
        }

        if (cardPlayed < 11) {
            // Take a turn
            pile[lenPile] = players[playing][0];
            lenPlayers[playing]--;
            cardPlayed = players[playing][0];
            // Remove the card from the players hand
            for(k = 0; k < lenPlayers[playing] ; k++) {
                players[playing][k] = players[playing][k + 1];
            }
            // Increase pile length
            lenPile++;
        } else {
            // Penalty turn
            int penalty = cardPlayed - 10;
            // Check if the player has enough cards to pay the penalty 
            if (penalty > lenPlayers[playing]) {
                penalty = lenPlayers[playing];
                if (talkative) {
                    printf("Player %d has less than %d cards so they have to lay all their cards" , playing, penalty);
                    printf("\n");
                }
            }

            // Add the penalty cards to the pile
            for (k = 0; k < penalty; k++) {
                pile[lenPile] = players[playing][k];
                lenPlayers[playing] = lenPlayers[playing] - 1;
                lenPile++;
                int l;
                // Remove the card from the players hand
                for(l = 0; l < lenPlayers[playing] ; l++) {
                    players[playing][l] = players[playing][l + 1];
                }
            }

            // Make sure the player receiving the cards still has cards and is playing
            int m = 0;
            while(m != 1){
                if (playing == 0 ){
                    playing = Nplayers - 1;
                    if (lenPlayers[playing] == 0) {
                        playing--;
                    } else {
                        m = 1;
                    }  
                } else {
                    playing--;
                    if (lenPlayers[playing] == 0) {
                        continue;
                    } else {
                        m = 1;
                    }
                }
            }

            // Add the pile to the players hand
            for (k=0; k < lenPile; k++) {
                i = lenPlayers[playing];
                players[playing][i] = pile[k];
                lenPlayers[playing]++;
                i++;
            }
            // Reset the pile
            for (i = 0; i < 52; i++) {
                pile[i] = 0;
            }
            lenPile = 0;
            cardPlayed = 0;            
        }

        // Reset players turn if over the amount of players
        if (playing == Nplayers - 1) {
            playing = 0;
        } else {
            playing++;
        }

        // Check if the next player has cards
        int n = 0;
        while(n != 1){
            if (lenPlayers[playing] == 0) {
                if (playing == Nplayers - 1) {
                    playing = 0;
                } else {
                    playing++;
                }
            } else {
                n = 1;
            }
        }

        // Check if someone won and if not change the players turn
        int z = 1;
        for (i = 0; i < Nplayers; i++) {
            if (lenPlayers[i] == 0) {
                z++;
            }
        }
        if (z == Nplayers) {
            won = 1;
            if (talkative) {
                printf("Player %d has won the game after %d turns.\n", playing, turns);
            }
            return turns;
        }
        // Add a turn
        turns++;

        // Game ends at 10000 turns if no one has won to save time and memory even though the game should never reach an infinite loop
        if (turns == 10000){
            if (talkative) {
                printf("The game has ended in a draw after 10000 turns.\n");
            }
            return 10000;
        }
    }
    return 0;
}
