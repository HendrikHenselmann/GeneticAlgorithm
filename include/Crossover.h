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
    // The population from which individuals are crossed over
    Population_t population;
    // The individuals that have been selected for crossover
    SelectedIndividuals_t selectedIndividuals;
} CrossoverParams_t;

// -----------------------------------------------------------------------------
// Initialization functions for the Crossover param struct
// -----------------------------------------------------------------------------

CrossoverParams_t initOnePointCrossoverParams(Population_t population, 
    SelectedIndividuals_t selectedIndividuals);
CrossoverParams_t initTwoPointCrossoverParams(Population_t population, 
    SelectedIndividuals_t selectedIndividuals);

// -----------------------------------------------------------------------------
// Different Crossover functions
// -----------------------------------------------------------------------------

SelectedIndividuals_t onePointCrossover(
    SelectedIndividuals_t selectedIndividuals);
SelectedIndividuals_t twoPointCrossover(
    SelectedIndividuals_t selectedIndividuals);

// -----------------------------------------------------------------------------

#endif  // CROSSOVER_H_
