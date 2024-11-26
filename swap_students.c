#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

// Function to print the array
void printArray(int arr[SIZE][SIZE]) {
    printf("Current Array:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
}

// Swap rows vertically (Row 1 <-> Row 8, Row 2 <-> Row 7, ...)
void swapRowsVertically(int arr[SIZE][SIZE]) {
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            int temp = arr[i][j];
            arr[i][j] = arr[SIZE - i - 1][j];
            arr[SIZE - i - 1][j] = temp;
        }
    }
    printf("Rows swapped vertically.\n");
}

// Swap columns horizontally (Column 1 <-> Column 4, Column 2 <-> Column 3, Column 5 <-> Column 8, ...)
void swapColumnsHorizontally(int arr[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 4; j++) {
            // Swap Column 1 with Column 4 and Column 5 with Column 8
            int temp = arr[i][j];
            arr[i][j] = arr[i][SIZE / 2 - j - 1];
            arr[i][SIZE / 2 - j - 1] = temp;

            temp = arr[i][SIZE / 2 + j];
            arr[i][SIZE / 2 + j] = arr[i][SIZE - j - 1];
            arr[i][SIZE - j - 1] = temp;
        }
    }
    printf("Columns swapped horizontally.\n");
}

// Randomize elements of the array without repetition
void randomizeElements(int arr[SIZE][SIZE]) {
    int temp[SIZE * SIZE];
    int index = 0;

    // Flatten the array into a 1D array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[index++] = arr[i][j];
        }
    }

    // Shuffle the flattened array using Fisher-Yates shuffle
    for (int i = SIZE * SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int swapTemp = temp[i];
        temp[i] = temp[j];
        temp[j] = swapTemp;
    }

    // Reconstruct the 2D array
    index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[i][j] = temp[index++];
        }
    }

    printf("Array elements randomized.\n");
}

// Menu-driven program
void menuDrivenProgram(int arr[SIZE][SIZE]) {
    // Array of function pointers
    void (*operations[])(int[SIZE][SIZE]) = {swapRowsVertically, swapColumnsHorizontally, randomizeElements};
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Swap Rows Vertically\n");
        printf("2. Swap Columns Horizontally\n");
        printf("3. Randomize Elements\n");
        printf("4. Stop\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            operations[choice - 1](arr); // Call the corresponding operation
            printArray(arr);            // Print the updated array
        } else if (choice != 4) {
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    printf("Program stopped.\n");
}

int main() {
    int arr[SIZE][SIZE];
    int value = 1;

    // Initialize the array with values 1 to 64
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[i][j] = value++;
        }
    }

    srand(time(NULL)); // Seed for randomization

    printf("Initial Array:\n");
    printArray(arr);

    menuDrivenProgram(arr);

    return 0;
}

