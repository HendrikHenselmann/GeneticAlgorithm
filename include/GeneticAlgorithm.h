// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include "./DTypes.h"

#include "./Selection.h"
#include "./Crossover.h"

// The parameters for the Genetic Algorithm Function
typedef struct GAParams_ {
    // Number of genes (bits) per individual
    size_t individualSize;
    // Number of individuals forming the population
    size_t populationSize;
    // Number of evolution steps
    unsigned long numEvolutions;
    // Ratio of top individuals surviving without modification (no mutation or
    // crossover)
    float elitismRatio;
    // Probability of a childs gene mutating (flipping)
    float mutationProbability;
    // Selection function
    SelectionParams_t selectionParams;
    SelectedIndividuals_t (*selectionFunc) (SelectionParams_t params);
    // Crossover function
    CrossoverParams_t crossoverParams;
    void (*crossoverFunc) (CrossoverParams_t params);
    // Fitness function
    FitnessScores_t (*populationFitnessFunc) (Population_t population);
} GAParams_t;

// Running the Genetic Algorithm based on the given parameters
Population_t runGeneticAlgorithm(GAParams_t params);

#endif  // GENETICALGORITHM_H_
