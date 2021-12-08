// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

// ----------------------------------------------------------------------------
// Imports
// ----------------------------------------------------------------------------
// External headers
#include <stdlib.h>
// Internal headers
#include "DTypes.h"
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
int knapsack_fitness(Individual_t individual);
// Display the problem
void knapsack_displayProblem(void);
// Display an Individual interpreted according to the problem
void knapsack_displayIndividual(Individual_t individual);
// Calculate the optimal solution
int knapsack_calcOptimum(void);
// ----------------------------------------------------------------------------

#endif  // KNAPSACK_H_
