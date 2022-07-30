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

    Population_t pop1 = initializePopulation(2, NUM_ITEMS);
    if (!pop1) {return -1;};

    printPopulation(pop1);

    mutate_population(pop1, MUTATION_PROBABILITY);

    printPopulation(pop1);


    freePopulation(pop1);


    // mutate(ind1, NUM_ITEMS, 0.5);

    // long counter = 0;

    // for (long x = 0; x < NUM_ITEMS; x++) {

    //     if (ind1[x]) {
    //         counter ++;
    //     }
    // }

    // float ratio = (float) counter/NUM_ITEMS;

    // printf("Of %ld items there are %ld true values which is a ratio of %f",
    //    NUM_ITEMS, counter, ratio);

    // free(ind1);

    return 0;
}
