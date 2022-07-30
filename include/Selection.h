// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef SELECTION_H_
#define SELECTION_H_

#include "./DTypes.h"

// Selecting individuals for the crossover step

// Random Selection
SelectedIndividuals_t randomSelection(
    Population_t population, size_t numSelectedPairs);

// Roulette Wheel Selection
SelectedIndividuals_t rouletteSelection(
    Population_t population, size_t numSelectedPairs,
    FitnessScores_t fitnessScores);

// Tournament Selection
// numSelectedPairs is the amount of individuals that are selected overall
// opposed to tournamentSize, which is the size of selected individuals
// of every tournament
SelectedIndividuals_t tournamentSelection(
    Population_t population, size_t numSelectedPairs,
    FitnessScores_t fitnessScores, size_t tournamentSize);

#endif  // SELECTION_H_
