// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../include/Crossover.h"

CrossoverParams_t initOnePointCrossoverParams(void) {

    return (CrossoverParams_t) {};
}

CrossoverParams_t initTwoPointCrossoverParams(void) {
    
    return (CrossoverParams_t) {};
}

// For every pair of parents that are crossed over to form 2 children, one point
// is randomly chosen. All genes up to that point of parent 1 are then passed
// to children 1. The remaining genes of parent 1 are passed on to children 2.
// For parent 2 it's the other way around.
void onePointCrossover(CrossoverParams_t params) {

    // Loop thorugh pairs of individuals that will be crossed over
    for (size_t i = 0; i < params.selectedIndividuals->numPairs; i++) {

        // Selected parents
        Individual_t parent1 = params.selectedIndividuals->array[2*i];
        Individual_t parent2 = params.selectedIndividuals->array[2*i+1];

        // Offspring destination
        Individual_t offspring1 = 
            params.population->array[params.numElitists + 2*i];
        Individual_t offspring2 = 
            params.population->array[params.numElitists + 2*i+1];

        // Randomly choose a crossover point
        size_t crossPoint = rand() %
            ((params.population->individualSize / params.geneLength) - 1);

        // Execute crossover process
        memcpy(offspring1, parent1,
            crossPoint*params.geneLength*sizeof(bool));
        memcpy(&(offspring1[crossPoint*params.geneLength]), parent2,
            (params.population->individualSize-crossPoint*params.geneLength)
                *sizeof(bool));
        memcpy(offspring2, parent2, crossPoint*params.geneLength*sizeof(bool));
        memcpy(&(offspring2[crossPoint*params.geneLength]), parent1,
            (params.population->individualSize-crossPoint*params.geneLength)
                *sizeof(bool));
    }
}

// TODO: Same as One Point Crossover but with 2 randomly selected split points.
void twoPointCrossover(CrossoverParams_t params) {}
