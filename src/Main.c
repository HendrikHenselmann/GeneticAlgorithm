// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Knapsack.h"
#include "../include/Selection.h"
// #include "../include/Mutation.h"
#include "../include/PopulationInitialization.h"

int main() {
    
    // Set random seed. This should be done once for the the whole program!
    // It is very important that this is the only place where srand is called!
    srand(time(NULL));

    // Display Problem
    knapsack_displayProblem();

    // Initialize Population
    Population_t population = initializePopulation(10, NUM_ITEMS, 0.2);
    if (!population) return EXIT_FAILURE;

    // Select individuals for the crossover step
    size_t numSelectionPairs = 2;
    SelectionParams_t params =
        initRandomSelectionParams(population, numSelectionPairs);
    SelectedIndividuals_t selection =
        randomSelection(params);
    if (!selection) return EXIT_FAILURE;

    // Display selected individuals
    for (size_t i = 0; i < 2*numSelectionPairs; i++) {
        knapsack_displayIndividual(population->array[selection->array[i]]);
    }

    // Free all memory allocations
    freeSelectedIndividuals(selection);
    freePopulation(population);

    return 0;
}
