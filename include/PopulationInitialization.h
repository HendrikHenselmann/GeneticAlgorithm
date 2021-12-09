// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef POPULATIONINITIALIZATION_H_
#define POPULATIONINITIALIZATION_H_

#include "./DTypes.h"

// Initializing a random population
// Returning NullPointer if some error occures, else the initialized random population
Population_t initializePopulation(size_t populationSize, size_t individualSize);

#endif  // POPULATIONINITIALIZATION_H_
