// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef MUTATION_H_
#define MUTATION_H_

#include "DTypes.h"

void mutate_individual(Individual_t individual, int size_of_individual, float probability);
void mutate_population(Population_t population, float probability);

#endif