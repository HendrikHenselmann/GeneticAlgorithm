// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include "./DTypes.h"

SelectedIndividuals_t onePointCrossover(SelectedIndividuals_t selectedIndividuals);
SelectedIndividuals_t twoPointCrossover(SelectedIndividuals_t selectedIndividuals);

#endif  // CROSSOVER_H_
