// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

// ----------------------------------------------------------------------------
// Imports
// ----------------------------------------------------------------------------
// External headers
#include <stdlib.h>
// Project headers
#include "./DTypes.h"
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Macros
// ----------------------------------------------------------------------------
// Knapsack
#define KNAPSACK_WEIGHT_CAP 100
// Items
#define NUM_ITEMS 10
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Module specific struct
// ----------------------------------------------------------------------------
// Item struct
typedef struct {
    int weight;
    int value;
} Item_t;
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Functions
// ----------------------------------------------------------------------------
// Calculate the fitness function of an individual according to the problem
float knapsack_individualFitness(Individual_t individual);
// Calculate the fitness function of the whole population according to the
// problem
FitnessScores_t knapsack_populationFitness(Population_t population);
// Display the problem
void knapsack_displayProblem(void);
// Display an Individual interpreted according to the problem
void knapsack_displayIndividual(Individual_t individual);
// Calculate the optimal solution
// Returning INT_MIN to indicate failure of malloc
float knapsack_calcOptimum(void);
// ----------------------------------------------------------------------------

#endif  // KNAPSACK_H_
