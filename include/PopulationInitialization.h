// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef POPULATIONINITIALIZATION_H_
#define POPULATIONINITIALIZATION_H_

#include "./DTypes.h"

// Initializing a random population
// activeGeneProba is the probability that an individuals gene is 1
// Returning NullPointer if some error occures, else the initialized random
// population
Population_t initializePopulation(
    size_t populationSize, size_t individualSize, float activeGeneProba);

#endif  // POPULATIONINITIALIZATION_H_
