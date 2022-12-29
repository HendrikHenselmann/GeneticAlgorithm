// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include "./DTypes.h"

#include "./Selection.h"
#include "./Crossover.h"
#include "./Environment.h"

// The parameters for the Genetic Algorithm Function
// This struct should solely be initialized by the initialization function
// below.
typedef struct GAParams_ {
    // Environment. Including individualSize, which is the number of genes
    // (bits) per individual. Also including function to calculate Individual
    // and Population fitness.
    Environment_t env;
    // Number of individuals forming the population
    size_t populationSize;
    // Probability that an individuals gene is active ( / 1 / true )
    float activeGeneRate;
    // Number of evolution steps
    unsigned long numEvolutions;
    // Ratio of top individuals surviving without modification (no mutation or
    // crossover)
    float elitismRatio;
    // Probability of a childs gene mutating (flipping)
    float mutationProbability;
    // Selection function
    SelectionParams_t selectionParams;
    void (*selectionFunc) (SelectionParams_t params);
    // Crossover function
    CrossoverParams_t crossoverParams;
    void (*crossoverFunc) (CrossoverParams_t params);
    // Print options | 3: a lot, 2: less, 1: little, 0: none
    int verbosityLevel;
    char outputFile[256];
} GAParams_t;

// Assembling the Genetic Algorithm parameters
GAParams_t initGAParams(Environment_t env, size_t populationSize,
    float activeGeneRate, unsigned long numEvolutions, float elitismRatio,
    float mutationProbability,
    SelectionParams_t selectionParams,
    void (*selectionFunc) (SelectionParams_t params),
    CrossoverParams_t crossoverParams,
    void (*crossoverFunc) (CrossoverParams_t params),
    int verbosityLevel,
    char outputFile[]);

// Running the Genetic Algorithm based on the given parameters
Population_t runGeneticAlgorithm(GAParams_t params);

#endif  // GENETICALGORITHM_H_
