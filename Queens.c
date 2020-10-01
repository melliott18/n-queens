//-----------------------------------------------------------------------------
// Queens.c
//
// Compile: make
//
// Run: Usage: ./Queens [-v] number
//      Option: -v verbose output, print all solutions
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printUsageMessage() {
    printf("%s\n", "Usage: ./Queens [-v] number");
    printf("%s\n", "Option: -v verbose output, print all solutions");
    exit(EXIT_FAILURE);
}

// Check if a character is a number
int isNumber(char number[]) {
    int i = 0;

    // Check for negative numbers
    if (number[0] == '-') {
        i = 1;
    }
    for (; number[i] != 0; i++) {
        // Check for digit
        if (!isdigit(number[i])) {
            return 0;
        }
    }

    return 1;
}

void placeQueen(int** B, int n, int i, int j) {
    B[i][j] = 1;
    B[i][0] = j;

    int k;
    int l;

    // Decrement column below B[i][j]
    for (k = i + 1; k <= n; k++) {
        B[k][j] -= 1;
    }

    // Decrement lower left diagonal
    for (k = i + 1, l = j - 1; k <= n && l > 0; k++, l--) {
        B[k][l] -= 1;
    }

    // Decrement lower right diagonal
    for (k = i + 1, l = j + 1; k <= n && l <= n; k++, l++) {
        B[k][l] -= 1;
    }

    return;
}

void removeQueen(int** B, int n, int i, int j) {
    B[i][j] = 0;
    B[i][0] = 0;

    int k;
    int l;

    // Increment column below B[i][j]
    for (k = i + 1; k <= n; k++) {
        B[k][j] += 1;
    }

    // Increment lower left diagonal
    for (k = i + 1, l = j - 1; k <= n && l > 0; k++, l--) {
        B[k][l] += 1;
    }

    // Increment lower right diagonal
    for (k = i + 1, l = j + 1; k <= n && l <= n; k++, l++) {
        B[k][l] += 1;
    }

    return;
}

void printBoard(int** B, int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (B[i][j] == 1) {
                printf("%s", "Q ");
            } else {
                printf("%s", "- ");
            }
        }
        printf("\n");
    }
    printf("\n");
    return;
}

int findSolutions(int** B, int n, int i, char* mode) {
    int num = 0;

    if (i > n) {
        if (strcmp(mode, "verbose") == 0) {
            printBoard(B, n);
        }

        return 1;

    }else {
        for (int j = 1; j <= n; j++) {
            if (B[i][j] == 0) {
                placeQueen(B, n, i, j);
                num += findSolutions(B, n, i + 1, mode);
                removeQueen(B, n, i, j);
            }
        }
    }

    return num;
}

int main(int argc, char* argv[]) {
    char* option;
    int n = 0;
    int count = 0;

    if (argc == 2) {
        if (!isNumber(argv[1])) {
            printUsageMessage();
        }

        option = "";
        n = atoi(argv[1]);

        if (n < 1) {
            printUsageMessage();
        }
    } else if (argc == 3) {
        if (strcmp(argv[1], "-v") != 0) {
            printUsageMessage();
        }

        if (!isNumber(argv[2])) {
            printUsageMessage();
        }

        option = "verbose";
        n = atoi(argv[2]);

        if (n < 1) {
            printUsageMessage();
        }
    } else {
        printUsageMessage();
    }

    int r = n + 1;
    int c = n + 1;
    int i, j;

    // Create a board of size (n + 1) by (n + 1)
    int **arr = (int **)malloc(r * sizeof(int *));

    for (i = 0; i < r; i++) {
        arr[i] = (int *)malloc(c * sizeof(int));
    }

    // Initialize the board elements to zero
    for (i = 0; i <  r; i++) {
        for (j = 0; j < c; j++) {
            arr[i][j] = 0;
        }
    }

    count = findSolutions(arr, n, 1, option);
    printf("%d", n);
    printf("%s", "-Queens has ");
    printf("%d", count);
    printf("%s\n", " solutions");

    for (int i = 0; i < n + 1; i++) {
        int* currentPtr = arr[i];
        free(currentPtr);
    }

    free(arr);

    return EXIT_SUCCESS;
}
