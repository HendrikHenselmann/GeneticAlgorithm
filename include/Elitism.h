// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef ELITISM_H_
#define ELITISM_H_

#include "./DTypes.h"

// Restructuring the population so that the first {numElitists} individuals of
// the population are the individuals that will survive unmodified.
// Restructuring the fitness score array accordingly.
// This is achieved by inplace sorting. O(n*log n)
void applyElitism(Population_t population, FitnessScores_t fitnessScores);

#endif  // ELITISM_H_
