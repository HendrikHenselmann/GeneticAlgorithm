// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef SELECTION_H_
#define SELECTION_H_

#include "./DTypes.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Selecting individuals for the crossover step
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Parameter of Selection functions
// Should only be initialized using the initialization functions below!
// -----------------------------------------------------------------------------

// Defining the input type for every Selection function
typedef struct {
    // The population from which individuals are selected
    Population_t population;
    // The number of pairs of individuals that are selected for crossover
    size_t numSelectedPairs;
    // The fitness scores corresponding to the population according to used
    // environment
    FitnessScores_t fitnessScores;
    // The size of a tournament. For Tournament selection only.
    size_t tournamentSize;
    // The already malloced struct which is used as return value
    SelectedIndividuals_t selectedIndividuals;
} SelectionParams_t;

// -----------------------------------------------------------------------------
// Initialization functions for the Selection param struct
// population and fitnessScores don't have to be set with those functions
// -----------------------------------------------------------------------------

SelectionParams_t initRandomSelectionParams(size_t numSelectedPairs);

SelectionParams_t initRouletteSelectionParams(size_t numSelectedPairs);

SelectionParams_t initTournamentSelectionParams(size_t numSelectedPairs,
    size_t tournamentSize);

// -----------------------------------------------------------------------------
// Different Selection functions
// -----------------------------------------------------------------------------

// Random Selection
SelectedIndividuals_t randomSelection(SelectionParams_t params);

// Roulette Wheel Selection
SelectedIndividuals_t rouletteSelection(SelectionParams_t params);

// Tournament Selection
// numSelectedPairs is the amount of individuals that are selected overall
// opposed to tournamentSize, which is the size of selected individuals
// of every tournament
SelectedIndividuals_t tournamentSelection(SelectionParams_t params);

// -----------------------------------------------------------------------------

#endif  // SELECTION_H_
