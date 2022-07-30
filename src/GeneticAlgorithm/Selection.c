// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include "../../include/Selection.h"

#include <stdlib.h>

SelectionParams_t initRandomSelectionParams(Population_t population,
    size_t numSelectedPairs) {

    return (SelectionParams_t) {
        .population = population,
        .numSelectedPairs = numSelectedPairs
    };
}

SelectionParams_t initRouletteSelectionParams(Population_t population,
    size_t numSelectedPairs, FitnessScores_t fitnessScores) {
    
    return (SelectionParams_t) {
        .population = population,
        .numSelectedPairs = numSelectedPairs,
        .fitnessScores = fitnessScores
    };
}

SelectionParams_t initTournamentSelectionParams(Population_t population,
    size_t numSelectedPairs, FitnessScores_t fitnessScores,
    size_t tournamentSize) {
    
    return (SelectionParams_t) {
        .population = population,
        .numSelectedPairs = numSelectedPairs,
        .fitnessScores = fitnessScores,
        .tournamentSize = tournamentSize
    };
}

// Random Selection
SelectedIndividuals_t randomSelection(SelectionParams_t params) {

    // Allocate memory for the SelectedIndividuals_t output
    SelectedIndividuals_t selectedIndividuals =
        createSelectedIndividuals(params.numSelectedPairs);

    // Select one pair at every iteration
    for (size_t i = 0; i < params.numSelectedPairs; i++) {

        // Select first parent
        int first = rand() % params.population->populationSize;

        // Select second parent. Check that first and second are not the same.
        int second = rand() % params.population->populationSize;
        while (first == second)
            second = rand() % params.population->populationSize;

        // Store them in the output array
        selectedIndividuals->array[2*i] = first;
        selectedIndividuals->array[2*i+1] = second;

    }

    return selectedIndividuals;
}

// Roulette Wheel Selection
SelectedIndividuals_t rouletteSelection(SelectionParams_t params) {

}

// Tournament Selection
// numSelectedPairs is the amount of individuals that are selected overall
// opposed to tournamentSize, which is the size of selected individuals
// of every tournament
SelectedIndividuals_t tournamentSelection(SelectionParams_t params) {

}
