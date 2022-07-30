// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>

#include "../../include/DTypes.h"

SelectedIndividuals_t createSelectedIndividuals(size_t numPairs) {

    // Allocate memory for the actual array
    Individual_t *individualArray = malloc(2*numPairs*sizeof(Individual_t));
    if (!individualArray) return NULL;

    // Allocate memory for the struct
    SelectedIndividuals_t selectedIndividuals = malloc(sizeof(SelectedIndividuals_t));
    if (!selectedIndividuals) {
        free(individualArray);
        return NULL;
    }

    // Fill the struct
    selectedIndividuals->size = 2*numPairs;
    selectedIndividuals->array = individualArray;

    return selectedIndividuals;
}

FitnessScores_t createFitnessScores(size_t size) {
    
    // Allocate memory for the actual array
    float *fitnessArray = malloc(size*sizeof(float));
    if (!fitnessArray) return NULL;

    // Allocate memory for the struct
    FitnessScores_t fitnessScores = malloc(sizeof(FitnessScores_t));
    if (!fitnessScores) {
        free(fitnessArray);
        return NULL;
    }

    // Fill the struct
    fitnessScores->size = size;
    fitnessScores->array = fitnessArray;

    return fitnessScores;
}

// Freeing all the allocated memory.
void freePopulation(Population_t population) {
    // Free the memory of Individuals.
    for (size_t indiIndex = 0; indiIndex < population->populationSize; indiIndex++) {
        free(population->array[indiIndex]);
    }
    // Free the array of Individuals.
    free(population->array);
    // Free the population struct.
    free(population);
}

void freeSelectedIndividuals(SelectedIndividuals_t selectedIndividuals) {
    // Free the memory of Individuals.
    for (size_t indiIndex = 0; indiIndex < selectedIndividuals->size; indiIndex++) {
        free(selectedIndividuals->array[indiIndex]);
    }
    // Free the array of Individuals.
    free(selectedIndividuals->array);
    // Free the struct.
    free(selectedIndividuals);
}

void freeFitnessScores(FitnessScores_t fitnessScores) {
    // Free memory of the array containing fitness scores.
    free(fitnessScores->array);
    // Free the struct.
    free(fitnessScores);
}

void printIndividual(Individual_t individual, size_t individualSize) {
    printf("\nIndividual:\n===========\n");
    for (size_t i = 0; i < individualSize; i++) {
        printf("%d", individual[i]);
    }
    printf("\n");
}

void printPopulation(Population_t population) {
    char separator[] = "======================================================================";
    printf("\nPopulation:\n");
    printf("%s\n", separator);
    for (size_t indiIndex = 0; indiIndex < population->populationSize; indiIndex++) {
        for (size_t i = 0; i < population->individualSize; i++) {
        printf("%d", population->array[indiIndex][i]);
        }
        printf("\n");
    }
    printf("%s\n\n", separator);
}
