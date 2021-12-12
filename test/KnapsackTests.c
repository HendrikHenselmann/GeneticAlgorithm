// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/Knapsack.h"

int main() {
// ----------------------------------------------------------------------------
    // Re-Defining Macro for tests
// ----------------------------------------------------------------------------
    #undef NUM_ITEMS
    #define NUM_ITEMS 10
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
    // Re-Defining Variable for tests
// ----------------------------------------------------------------------------
    Item_t itemList[NUM_ITEMS] = {
    {4, 19},
    {24, 12},
    {32, 10},
    {53, 32},
    {12, 10},
    {63, 37},
    {35, 28},
    {12, 8},
    {44, 36},
    {70, 61}
    };
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
    // Define Individuals for tests
// ----------------------------------------------------------------------------
    Individual_t indi1 = calloc(NUM_ITEMS, sizeof(bool));
    Individual_t indi2 = malloc(NUM_ITEMS * sizeof(bool));
    memset(indi2, true, sizeof(bool) * NUM_ITEMS);
    Individual_t indi3 = calloc(NUM_ITEMS, sizeof(bool));
    indi3[0] = true;
    Individual_t indi4 = calloc(NUM_ITEMS, sizeof(bool));
    indi4[5] = true;
    Individual_t indi5 = calloc(NUM_ITEMS, sizeof(bool));
    indi5[NUM_ITEMS-1] = true;
    Individual_t indi6 = calloc(NUM_ITEMS, sizeof(bool));
    indi6[1] = true;
    indi6[4] = true;
    indi6[6] = true;
    Individual_t indi7 = calloc(NUM_ITEMS, sizeof(bool));
    indi7[1] = true;
    indi7[5] = true;
    indi7[6] = true;
    Individual_t indi8 = calloc(NUM_ITEMS, sizeof(bool));
    indi8[0] = true;
    indi8[4] = true;
    indi8[7] = true;
    indi8[9] = true;
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
    // Tests of the Fitness function
// ----------------------------------------------------------------------------
    assert(knapsack_individualFitness(indi1) == 0);
    assert(knapsack_individualFitness(indi2) == 0);
    assert(knapsack_individualFitness(indi3) == 19);
    assert(knapsack_individualFitness(indi4) == 37);
    assert(knapsack_individualFitness(indi5) == 61);
    assert(knapsack_individualFitness(indi6) == 50);
    assert(knapsack_individualFitness(indi7) == 0);
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
    // Tests of the optimal solution function
// ----------------------------------------------------------------------------
    assert(knapsack_calcOptimum() == 98);
    assert(knapsack_calcOptimum() == knapsack_individualFitness(indi8));
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
    // Free all memory allocations
// ----------------------------------------------------------------------------
    free(indi1);
    free(indi2);
    free(indi3);
    free(indi4);
    free(indi5);
    free(indi6);
    free(indi7);
    free(indi8);
// ----------------------------------------------------------------------------

    return 0;
}
