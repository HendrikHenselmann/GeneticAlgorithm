#include <stdio.h>
#include <stdlib.h>

#include "../include/Knapsack.h"

int main() {
    // Test Individuals
    Individual_t indi1 = calloc(NUM_ITEMS, sizeof(bool));
    Individual_t indi2 = malloc(NUM_ITEMS * sizeof(bool));
    memset (indi2, true, sizeof(bool) * NUM_ITEMS);

    // Display Problem
    knapsack_displayProblem();

    // Display Individual
    knapsack_displayIndividual(indi1);
    knapsack_displayIndividual(indi2);

    // Free all memory allocations
    free(indi1);
    free(indi2);

    return 0;
}
