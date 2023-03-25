#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pig.h"


int main() {
    // Test cases
    char* words[] = {
        "happy",
        "duck",
        "glove",
        "evil",
        "eight",
        "yowler",
        "crystal"
    };
    char* expected[] = {
        "appyhay",
        "uckday",
        "oveglay",
        "evilway",
        "eightway",
        "owleryay",
        "ystalcray"
    };

    int n = sizeof(words) / sizeof(words[0]);
    
    // Tests each word with the expected result
    int i;
    for (i = 0; i < n; i++) {
        char* result = pig(words[i]);
        if (strcmp(result, expected[i]) != 0) {
            printf("FAIL: pig(\"%s\") returned \"%s\", expected \"%s\")\n",
                   words[i], result, expected[i]);
            return 1;
        }
        free(result);
    }
    printf("PASS\n");
    return 0;
}
