// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include "./DTypes.h"

// The parameters for the Genetic Algorithm Function
typedef struct GAParams_ {
    size_t individualSize;
    size_t populationSize;
    unsigned long numGenerations;
    float elitismRatio;
    float mutationProbability;
    SelectedIndividuals_t (*crossoverFunction) (SelectedIndividuals_t selectedIndividuals);
    void (*populationFitnessFunction) (Population_t population);
} GAParams_t;

// Running the Genetic Algorithm based on the given parameters
Population_t runGeneticAlgorithm(GAParams_t params);

#endif  // GENETICALGORITHM_H_
