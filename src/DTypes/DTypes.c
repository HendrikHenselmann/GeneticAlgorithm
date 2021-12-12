// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>

#include "../../include/DTypes.h"

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
