// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>

#include "../../include/DTypes.h"

SelectedIndividuals_t initSelectedIndividuals(size_t numPairs,
    size_t individualSize) {

    // Allocate memory for the actual array
    Individual_t *individualArray = malloc(2*numPairs*sizeof(Individual_t));
    if (!individualArray) return NULL;

    // Allocate the individuals in the array
    for (size_t i = 0; i < 2*numPairs; i++) {
        Individual_t individual = (bool *) malloc(individualSize*sizeof(bool));
        if (!individual) {
            for (size_t j = 0; j < i; j++) {
                free(individualArray[j]);
            }
            free(individualArray);
            return NULL;
        }
        individualArray[i] = individual;
    }

    // Allocate memory for the struct
    SelectedIndividuals_t selectedIndividuals =
        malloc(sizeof(struct SelectedIndividuals_));
    if (!selectedIndividuals) {
        for (size_t i = 0; i < 2*numPairs; i++) {
            free(individualArray[i]);
        }
        free(individualArray);
        return NULL;
    }

    // Fill the struct
    selectedIndividuals->numPairs = numPairs;
    selectedIndividuals->array = individualArray;

    return selectedIndividuals;
}

FitnessScores_t initFitnessScores(size_t size) {
    
    // Allocate memory for the actual array
    float *fitnessArray = malloc(size*sizeof(float));
    if (!fitnessArray) return NULL;

    // Allocate memory for the struct
    FitnessScores_t fitnessScores = malloc(sizeof(struct FitnessScores_));
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
    for (size_t indiIndex = 0;
        indiIndex < population->populationSize;
        indiIndex++) {
        free(population->array[indiIndex]);
    }
    // Free the array of Individuals.
    free(population->array);
    // Free the population struct.
    free(population);
}

void freeSelectedIndividuals(SelectedIndividuals_t selectedIndividuals) {
    // Free all the individuals
    for (size_t i = 0; i < 2*selectedIndividuals->numPairs; i++) {
        free(selectedIndividuals->array[i]);
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

// Get the fittest individuals index of a population
size_t fittestIndividual(FitnessScores_t fitnessScores) {

    size_t fittestIndex = 0;
    float fittestFitness = fitnessScores->array[0];

    for (size_t i = 1; i < fitnessScores->size; i++) {
        if (fitnessScores->array[i] > fittestFitness) {
            fittestIndex = i;
            fittestFitness = fitnessScores->array[i];
        }
    }

    return fittestIndex;
}

void printFitnessScores(FitnessScores_t fitnessScores) {
    printf("[");
    for(size_t i = 0; i < fitnessScores->size; i++) {
        printf(" %.3f", fitnessScores->array[i]);
    }
    printf(" ]\n");
}

void printIndividual(Individual_t individual, size_t individualSize) {
    printf("\nIndividual:\n===========\n");
    for (size_t i = 0; i < individualSize; i++) {
        printf("%d", individual[i]);
    }
    printf("\n");
}

void printPopulation(Population_t population) {

    char separator[] = "=======================================================\
===============";

    printf("\nPopulation:\n");
    printf("%s\n", separator);

    for (size_t indiIndex = 0;
        indiIndex < population->populationSize;
        indiIndex++) {

        for (size_t i = 0; i < population->individualSize; i++) {
        printf("%d", population->array[indiIndex][i]);
        }
        printf("\n");

    }

    printf("%s\n\n", separator);
}
