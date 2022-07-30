// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef DTYPES_H_
#define DTYPES_H_

#include <stdio.h>
#include <stdbool.h>

// Individual
typedef bool *Individual_t;

// Population
typedef struct Population_ {
    size_t populationSize;
    size_t individualSize;
    Individual_t *array;
} *Population_t;

// Sub-population that is selected in the Selection step.
// 2 consecutive Individuals are chosen to be crossed over.
// The selected individuals are represented by their index in the population.
typedef struct SelectedIndividuals_ {
    size_t size;
    size_t *array;
} *SelectedIndividuals_t;

// Array of fitness scores corresponding to a population
typedef struct FitnessScores_ {
    size_t size;
    float *array;
} *FitnessScores_t;

// Initialize structs. Population initialization is a seperate component
SelectedIndividuals_t createSelectedIndividuals(size_t numPairs);
FitnessScores_t createFitnessScores(size_t size);

// Freeing all the allocated memory.
void freePopulation(Population_t population);
void freeSelectedIndividuals(SelectedIndividuals_t selectedIndividuals);
void freeFitnessScores(FitnessScores_t fitnessScores);

// Pretty printing functions
void printIndividual(Individual_t individual, size_t individualSize);
void printPopulation(Population_t population);

#endif  // DTYPES_H_
