// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef MUTATION_H_
#define MUTATION_H_

#include "DTypes.h"

// Randomly flip bits of the individual
void mutateIndividual(Individual_t individual, size_t individualSize,
    float probability);
// Randomly flip bits of offsprings in population
void mutatePopulation(Population_t population, size_t numElitists, float probability);

// Flip bit with index bitIndex of given individual
// It is used by mutateIndividual and mutatePopulation
// Assumption: bitIndex < size of individual
// This function is declared here to be able to test it.
void flipBit (Individual_t individual, size_t bitIndex);

#endif
