#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#include "../include/Mutation.h"

long NUM_ITEMS = 5;

int main() {
    Individual_t ind1 = calloc(NUM_ITEMS, sizeof(bool));
    Individual_t ind2 = calloc(NUM_ITEMS, sizeof(bool));
    Population_t pop1 = malloc(sizeof(ind1) * 2 + sizeof(Population_t));
    pop1[0] = ind1;
    pop1[1] = ind2;

    mutate_population(pop1, 5, 2);


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
