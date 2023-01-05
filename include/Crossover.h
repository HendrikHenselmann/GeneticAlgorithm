// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include "./DTypes.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Crossover: Combining 2 individuals from one generation to form 2 new
//            individuals that will be part of the next generation
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Parameter of Crossover functions
// Should solely be initialized using the initialization functions below!
// -----------------------------------------------------------------------------

// Defining the input type for every Crossover function
typedef struct {
    // The population from which individuals are crossed over.
    // It will also be updated inplace by the function.
    Population_t population;
    // The individuals that have been selected for crossover.
    SelectedIndividuals_t selectedIndividuals;
    // Number of individuals that survive unmodified. This is needed to know
    // where the new children are stored that are formed at the crossover step.
    size_t numElitists;
    // The length of one gene of an individual.
    // Prevents splitting a gene which would result in the loss of information.
    size_t geneLength;
} CrossoverParams_t;

// -----------------------------------------------------------------------------
// Initialization functions for the Crossover param struct
// population and selectedIndividuals don't have to be set with those functions
// -----------------------------------------------------------------------------

CrossoverParams_t initOnePointCrossoverParams(void);
CrossoverParams_t initTwoPointCrossoverParams(void);

// -----------------------------------------------------------------------------
// Different Crossover functions
// -----------------------------------------------------------------------------

// For every pair of parents that are crossed over to form 2 children, one point
// is randomly chosen. All genes up to that point of parent 1 are then passed
// to children 1. The remaining genes of parent 1 are passed on to children 2.
// For parent 2 it's the other way around.
void onePointCrossover(CrossoverParams_t params);

// Same as One Point Crossover but with 2 randomly selected split points.
// Note: If both randomly selected split points are equal the function is
//       basically copying the parents.
void twoPointCrossover(CrossoverParams_t params);

// -----------------------------------------------------------------------------
// Internal functions that shall be tested
// -----------------------------------------------------------------------------

// Copying one section starting from element start with length numBooleans
// of parent to offspring
void copyIndividualSegment(Individual_t offspring, Individual_t parent,
    size_t start, size_t numBooleans);

// -----------------------------------------------------------------------------

#endif  // CROSSOVER_H_
