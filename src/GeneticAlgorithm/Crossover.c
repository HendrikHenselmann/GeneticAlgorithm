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

// Copying one section starting from element start with length numBooleans
// of parent to offspring
void copyIndividualSegment(Individual_t offspring, Individual_t parent,
    size_t start, size_t numBooleans) {

    memcpy(&(offspring[start]), &(parent[start]), numBooleans * sizeof(bool));

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
            (params.population->individualSize / params.geneLength);

        // Calculate segment start points and lengths
        size_t segment1Len = crossPoint*params.geneLength;
        size_t segment2Start = crossPoint*params.geneLength;
        size_t segment2Len =
            params.population->individualSize-crossPoint*params.geneLength;

        // Execute crossover process
        copyIndividualSegment(offspring1, parent1, 0, segment1Len);
        copyIndividualSegment(offspring2, parent2, 0, segment1Len);

        copyIndividualSegment(offspring2, parent1, segment2Start,
            segment2Len);
        copyIndividualSegment(offspring1, parent2, segment2Start,
            segment2Len);

    }
}

// Same as One Point Crossover but with 2 randomly selected split points.
// Note: If both randomly selected split points are equal the function is
//       basically copying the parents.
void twoPointCrossover(CrossoverParams_t params) {

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

        // Randomly choose two crossover point
        size_t crossPoint1 = rand() %
            ((params.population->individualSize / params.geneLength) - 1);
        size_t crossPoint2 = rand() %
            ((params.population->individualSize / params.geneLength) - 1);

        // Sort crossPoint1 and crossPoint2 by potentially switching
        if (crossPoint2 < crossPoint1) {
            size_t temp = crossPoint2;
            crossPoint2 = crossPoint1;
            crossPoint1 = temp;
        }

        // Execute crossover of the first section
        size_t segment1Len = crossPoint1*params.geneLength;
        copyIndividualSegment(offspring1, parent1, 0, segment1Len);
        copyIndividualSegment(offspring2, parent2, 0, segment1Len);

        // Execute crossover of the second section
        size_t segment2Start = crossPoint1*params.geneLength;
        size_t segment2Len =
            crossPoint2*params.geneLength-crossPoint1*params.geneLength;
        copyIndividualSegment(offspring2, parent1, segment2Start,
            segment2Len);
        copyIndividualSegment(offspring1, parent2, segment2Start,
            segment2Len);

        // Execute crossover of the third section
        size_t segment3Start = crossPoint2*params.geneLength;
        size_t segment3Len =
            params.population->individualSize-crossPoint2*params.geneLength;
        copyIndividualSegment(offspring1, parent1, segment3Start,
            segment3Len);
        copyIndividualSegment(offspring2, parent2, segment3Start,
            segment3Len);
    }
}
