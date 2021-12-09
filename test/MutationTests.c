#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#include "../include/Mutation.h"

long NUM_ITEMS = 5;

int main() {
    Individual_t ind1 = calloc(NUM_ITEMS, sizeof(bool));
    Individual_t ind2 = calloc(NUM_ITEMS, sizeof(bool));
    Individual_t *array = malloc(sizeof(Individual_t) * 2);
    Population_t pop1 = {
        .populationSize = 2,
        .individualSize = NUM_ITEMS,
        .array= array
    };
    pop1.array[0] = ind1;
    pop1.array[1] = ind2;

    printPopulation(pop1);

    mutate_population(pop1, 0.5);

    printPopulation(pop1);


    // mutate(ind1, NUM_ITEMS, 0.5);

    // long counter = 0;

    // for (long x = 0; x < NUM_ITEMS; x++) {

    //     if (ind1[x]) {
    //         counter ++;
    //     }
    // }

    // float ratio = (float) counter/NUM_ITEMS;

    // printf("Of %ld items there are %ld true values which is a ratio of %f", NUM_ITEMS, counter, ratio);

    // free(ind1);

    return 0;
}
