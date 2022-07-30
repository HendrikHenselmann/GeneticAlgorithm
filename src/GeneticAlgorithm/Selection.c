// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include "../../include/Selection.h"

#include <stdlib.h>

// Random Selection
SelectedIndividuals_t randomSelection(
    Population_t population, size_t numSelectedPairs) {

    // Allocate memory for the SelectedIndividuals_t output
    SelectedIndividuals_t selectedIndividuals =
        createSelectedIndividuals(numSelectedPairs);

    // Select one pair at every iteration
    for (size_t i = 0; i < numSelectedPairs; i++) {

        // Select first parent
        int first = rand() % population->populationSize;

        // Select second parent. Check that first and second are not the same.
        int second = rand() % population->populationSize;
        while (first == second) second = rand() % population->populationSize;

        // Store them in the output array
        selectedIndividuals->array[2*i] = population->array[first];
        selectedIndividuals->array[2*i+1] = population->array[second];

    }

    return selectedIndividuals;
}

// Roulette Wheel Selection
SelectedIndividuals_t rouletteSelection(
    Population_t population, size_t numSelectedPairs,
    FitnessScores_t fitnessScores) {

}

// Tournament Selection
// numSelectedPairs is the amount of individuals that are selected overall
// opposed to tournamentSize, which is the size of selected individuals
// of every tournament
SelectedIndividuals_t tournamentSelection(
    Population_t population, size_t numSelectedPairs,
    FitnessScores_t fitnessScores, size_t tournamentSize) {

}
