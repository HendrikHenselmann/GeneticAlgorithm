// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef SELECTION_H_
#define SELECTION_H_

#include "./DTypes.h"

// Selecting individuals for the crossover step
SelectedIndividuals_t select(float elitismRatio, Population_t population);

#endif  // SELECTION_H_
