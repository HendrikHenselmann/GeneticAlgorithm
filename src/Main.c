// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Knapsack.h"
#include "../include/Mutation.h"

int main() {
    
    // Set random seed. This should be done once for the the whole program!
    // It is very important that this is the only place where srand is called!
    srand(time(NULL));

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
