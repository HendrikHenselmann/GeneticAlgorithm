// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>
#include <string.h>

#include "../../include/Selection.h"

SelectionParams_t initRandomSelectionParams(void) {

    return (SelectionParams_t) {};
}

SelectionParams_t initRouletteSelectionParams(void) {
    
    return (SelectionParams_t) {};
}

SelectionParams_t initTournamentSelectionParams(size_t tournamentSize) {
    
    return (SelectionParams_t) {
        .tournamentSize = tournamentSize
    };
}

// Random Selection
void randomSelection(SelectionParams_t params) {

    // Select one pair at every iteration
    for (size_t i = 0; i < params.numSelectedPairs; i++) {

        // Select first parent
        int first = rand() % params.population->populationSize;

        // Select second parent. Check that first and second are not the same.
        int second = rand() % params.population->populationSize;
        while (first == second)
            second = rand() % params.population->populationSize;

        // Store them in the output array of selected individuals
        memcpy(params.selectedIndividuals->array[2*i],
            params.population->array[first],
            params.population->individualSize * sizeof(bool));
        memcpy(params.selectedIndividuals->array[2*i+1],
            params.population->array[second],
            params.population->individualSize * sizeof(bool));
    }
}

// Roulette Wheel Selection
void rouletteSelection(SelectionParams_t params) {

}

// Tournament Selection
// numSelectedPairs is the amount of individuals that are selected overall
// opposed to tournamentSize, which is the size of selected individuals
// of every tournament
void tournamentSelection(SelectionParams_t params) {

}
