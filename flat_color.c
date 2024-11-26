#include <stdio.h>
#include <stdlib.h>

#define FLOOR 5   // Floors: 0 (GROUND) to 4 (TOP)
#define FACES 4   // Faces: SOUTH(0), EAST(1), WEST(2), NORTH(3)
#define SRLNO 3   // Serial numbers: Left to Right in each FACE: 0-2

// Define the color and grade arrays
char* color[FACES] = {"GREEN", "BROWN", "BLUE", "YELLOW"};
char* grade[FLOOR] = {"DEEP", "DARK", "MEDIUM", "MILD", "LIGHT"};

// Function to generate the flat number
char* FlatNo(int floor, int face, int srl) {
    char s[FACES] = {'S', 'E', 'W', 'N'};
    char *ret = (char *)malloc(4 * sizeof(char));  // Allocate memory for the flat number
    sprintf(ret, "%c%d%c", s[face], floor, 'A' + srl);
    return ret;
}

// Query function to display flat details
void query(int floor, int face, int srl) {
    if (floor < 0 || floor >= FLOOR || face < 0 || face >= FACES || srl < 0 || srl >= SRLNO) {
        printf("\nInvalid input! Please enter values within range.\n");
        return;
    }

    char* flatNumber = FlatNo(floor, face, srl);
    printf("\nFlat# %s has %s %s Windows\n", flatNumber, grade[floor], color[face]);
    free(flatNumber);  // Free allocated memory
}

// Main function
int main() {
    int floor, face, srl;

    // Prompt the user for inputs
    printf("Enter Floor#[0-%d], Face#[0-%d], Srl#[0-%d]: ", FLOOR - 1, FACES - 1, SRLNO - 1);
    scanf("%d,%d,%d", &floor, &face, &srl);

    // Process the query
    query(floor, face, srl);

    return 0;
}

