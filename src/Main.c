#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Knapsack.h"
#include "../include/Mutation.h"

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

    Individual_t ind1 = calloc(NUM_ITEMS, sizeof(bool));
    Individual_t ind2 = calloc(NUM_ITEMS, sizeof(bool));
    Population_t pop1 = malloc(sizeof(ind1) * 2);

    mutate_population(pop1, sizeof(ind1), sizeof(pop1));

    pop1[0] = ind1;
    pop1[1] = ind2;
    printf("im here");

    free(ind1);
    free(ind2);
    free(pop1);

    return 0;
}
