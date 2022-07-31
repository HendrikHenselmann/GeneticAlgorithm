// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef ELITISM_H_
#define ELITISM_H_

#include "./DTypes.h"

// Restructuring the population so that the first {numElitists} individuals of
// the population are the individuals that will survive unmodified.
// O(populationSize)
void applyElitism(Population_t population, size_t numElitists,
    FitnessScores_t fitnessScores);

#endif  // ELITISM_H_
