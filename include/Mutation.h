// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef MUTATION_H_
#define MUTATION_H_

#include "DTypes.h"

void mutate(Individual_t individual, int size_of_individual, float probability);
void mutate_population(Population_t *population, int size_of_individual, int size_of_population);

#endif