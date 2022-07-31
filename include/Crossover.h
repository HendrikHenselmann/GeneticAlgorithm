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
// Should only be initialized using the initialization functions below!
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

void onePointCrossover(CrossoverParams_t params);
void twoPointCrossover(CrossoverParams_t params);

// -----------------------------------------------------------------------------

#endif  // CROSSOVER_H_
