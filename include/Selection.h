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
// Population, numSelectedPairs and fitnessScores don't have to be set within
// those functions. They will be set or deduced by the GA function.
// -----------------------------------------------------------------------------

SelectionParams_t initRandomSelectionParams(void);

SelectionParams_t initRouletteSelectionParams(void);

SelectionParams_t initTournamentSelectionParams(size_t tournamentSize);

// -----------------------------------------------------------------------------
// Different Selection functions
// -----------------------------------------------------------------------------

// Random Selection
void randomSelection(SelectionParams_t params);

// Roulette Wheel Selection
void rouletteSelection(SelectionParams_t params);

// Tournament Selection
// numSelectedPairs is the amount of individuals that are selected overall
// opposed to tournamentSize, which is the size of selected individuals
// of every tournament
void tournamentSelection(SelectionParams_t params);

// -----------------------------------------------------------------------------
// Internal functions that shall be tested
// -----------------------------------------------------------------------------

// Copying the selected parents to their location in the array of selected
// individuals based on the current pairs id.
void copySelectedParents(Population_t population,
    SelectedIndividuals_t selectedIndividuals,
    size_t pairID, size_t parent1ID, size_t parent2ID);

// -----------------------------------------------------------------------------

#endif  // SELECTION_H_
