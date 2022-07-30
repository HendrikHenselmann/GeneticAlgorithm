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

    // Initialize the struct that stores selected individuals
    size_t numSelectionPairs = 2;
    SelectedIndividuals_t selectedIndis =
        initSelectedIndividuals(numSelectionPairs);
    if (!selectedIndis) {
        freePopulation(population);
        return EXIT_FAILURE;
    }

    // Actually select individuals for the crossover step
    SelectionParams_t params = initRandomSelectionParams(numSelectionPairs);
    params.population = population;
    params.selectedIndividuals = selectedIndis;
    selectedIndis = randomSelection(params);

    // Display selected individuals
    for (size_t i = 0; i < 2*numSelectionPairs; i++) {
        knapsack_displayIndividual(population->array[selectedIndis->array[i]]);
    }

    // Free all memory allocations
    freeSelectedIndividuals(selectedIndis);
    freePopulation(population);

    return 0;
}
