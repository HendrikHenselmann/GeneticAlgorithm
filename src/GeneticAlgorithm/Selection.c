// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>
#include <string.h>
#include <math.h>

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

// Copying the selected parents to their location in the array of selected
// individuals based on the current pairs id.
void copySelectedParents(Population_t population,
    SelectedIndividuals_t selectedIndividuals,
    size_t pairID, size_t parent1ID, size_t parent2ID) {

    memcpy(selectedIndividuals->array[2*pairID],
        population->array[parent1ID],
        population->individualSize * sizeof(bool));
    memcpy(selectedIndividuals->array[2*pairID+1],
        population->array[parent2ID],
        population->individualSize * sizeof(bool));

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

        // Store the selected parents in the output array selectedIndividuals
        copySelectedParents(params.population, params.selectedIndividuals,
            i, first, second);
    }
}

// Accumulating the fitness scores by iteratively adding the first to the second
// , the result to the third, this result to the fourth .. until the last
// elemnt of the fitness score array contains the accumulated sum of all scores.
void accumulateFitnessScores(FitnessScores_t fitnessScores) {

    for (size_t i = 1; i < fitnessScores->size; i++) {
        fitnessScores->array[i] += fitnessScores->array[i-1];
    }

}

// Undo what the accumulateFitnessScores function did
void revertFitnessScoresAccumulation(FitnessScores_t fitnessScores) {

    for (size_t i = fitnessScores->size-1; i > 0; i--) {
        fitnessScores->array[i] -= fitnessScores->array[i-1];
    }

}

size_t fitnessScoreToIndividual(FitnessScores_t fitnessScores,
    float precisionFactor, size_t fitnessScore) {

    for (size_t i = 0; i < fitnessScores->size; i++) {
        if (fitnessScore < fitnessScores->array[i] * precisionFactor)
            return i;
    }

    // This indicates failure. Accumulation or random fitness score drawing
    // are not implemented correctly.
    return fitnessScores->size;
}

// Roulette Wheel Selection
void rouletteSelection(SelectionParams_t params) {

    // Accumulate fitness scores
    accumulateFitnessScores(params.fitnessScores);

    // Store the sum of all fitness values
    float fitnessScoresSum =
        params.fitnessScores->array[params.fitnessScores->size-1];

    // If all fitness scores are 0 -> Do random selection
    // The code below would trigger a division by zero in the modulo operator
    if (fitnessScoresSum < 0.001) {
        randomSelection (params);
        return;
    }

    // Select one pair at every iteration
    for (size_t i = 0; i < params.numSelectedPairs; i++) {

        // Randomly generate two numbers from 0 to (factor * sum of all fitness
        // scores) - 1. The factor > 1 will increase precision.
        float precisionFactor = 100.0f;
        size_t scaledIntSum = round(precisionFactor*fitnessScoresSum);
        size_t firstScore = rand() % scaledIntSum;
        size_t secondScore = rand() % scaledIntSum;

        // Figuring out which individuals were just selected
        size_t first =
            fitnessScoreToIndividual(params.fitnessScores, precisionFactor,
                firstScore);
        size_t second =
            fitnessScoreToIndividual(params.fitnessScores, precisionFactor,
                secondScore);

        // Repeat selection of the second individual until the first and the
        // second parent are distinct.
        while (first == second) {

            secondScore = rand() % scaledIntSum;
            second =
                fitnessScoreToIndividual(params.fitnessScores, precisionFactor,
                    secondScore);

        }

        // Store the selected parents in the output array
        copySelectedParents(params.population, params.selectedIndividuals, i,
            first, second);

    }

    // Revert fitness score accumulation
    revertFitnessScoresAccumulation(params.fitnessScores);

}

// Tournament Selection
// numSelectedPairs is the amount of individuals that are selected overall
// opposed to tournamentSize, which is the size of selected individuals
// of every tournament
void tournamentSelection(SelectionParams_t params) {}
