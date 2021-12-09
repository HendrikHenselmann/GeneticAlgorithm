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

// Freeing all the allocated memory.
void freePopulation(Population_t population);

// Pretty printing functions
void printIndividual(Individual_t individual, size_t individualSize);
void printPopulation(Population_t population);

#endif  // DTYPES_H_
