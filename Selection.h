// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef SELECTION_H_
#define SELECTION_H_

#include <../../include/DTypes.h>

// Selecting individuals for the crossover step
Population_t select(float elitismRatio);

#endif  // SELECTION_H_
