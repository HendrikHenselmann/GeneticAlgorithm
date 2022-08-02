// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#include "../include/Mutation.h"
#include "../include/PopulationInitialization.h"

long NUM_ITEMS = 5;
float MUTATION_PROBABILITY = 0.5;

int main() {
    // Set random seed
    srand(128);

    Population_t pop1 = initializePopulation(2, NUM_ITEMS, 0.5);
    if (!pop1) {return -1;};

    printPopulation(pop1);

    mutatePopulation(pop1, 0, MUTATION_PROBABILITY);

    printPopulation(pop1);

    freePopulation(pop1);

    return 0;
}
