// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include "./DTypes.h"

#include "./Selection.h"
#include "./Crossover.h"

// The parameters for the Genetic Algorithm Function
// This struct should solely be initialized by the initialization function
// below.
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
    Population_t (*crossoverFunc) (CrossoverParams_t params);
    // Fitness function
    FitnessScores_t (*populationFitnessFunc) (Population_t population,
        FitnessScores_t fitnessScores);
} GAParams_t;

// Assembling the Genetic Algorithm parameters
GAParams_t initGAParams(size_t individualSize, size_t populationSize,
    unsigned long numEvolutions, float elitismRatio, float mutationProbability,
    SelectionParams_t selectionParams,
    SelectedIndividuals_t (*selectionFunc) (SelectionParams_t params),
    CrossoverParams_t crossoverParams,
    Population_t (*crossoverFunc) (CrossoverParams_t params),
    FitnessScores_t (*populationFitnessFunc) (Population_t population,
        FitnessScores_t fitnessScores)
);

// Running the Genetic Algorithm based on the given parameters
Population_t runGeneticAlgorithm(GAParams_t params);

#endif  // GENETICALGORITHM_H_
