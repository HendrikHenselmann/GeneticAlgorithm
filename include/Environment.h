// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "./DTypes.h"

typedef struct {
    // The size of an individual according to the environment
    size_t individualSize;
    // The length of one gene of the individual
    // Assumption: All genes are of the same length.
    size_t geneLength;
    // Displaying a description of the problem
    void (*displayProblem) (void);
    // Displaying the interpretation of one individual
    void (*displayIndividual) (Individual_t individual);
    // Displaying the interpretation of every individual of a population
    void (*displayPopulation) (Population_t population);
    // Calculating the fitness value of an individual
    float (*calcIndividualFitness) (Individual_t individual);
    // Calculating the fitness value of every individual of the population.
    // The fitness values will be written into fitnessScores.
    void (*calcPopulationFitness) (Population_t population,
        FitnessScores_t fitnessScores);
} Environment_t;

#endif  // ENVIRONMENT_H_
