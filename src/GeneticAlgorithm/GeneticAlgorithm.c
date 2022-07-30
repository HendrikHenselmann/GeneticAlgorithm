// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>

#include "../../include/Knapsack.h" // Delete when environment is variable
#include "../../include/PopulationInitialization.h"

#include "../../include/GeneticAlgorithm.h"

// Running the Genetic Algorithm based on the given parameters
Population_t runGeneticAlgorithm(GAParams_t params) {

    // Initializing population
    Population_t population =
        initializePopulation(params.populationSize, params.individualSize, 0.5);
    if (!population) {
        return NULL;
    }

    // Initializing a struct that stores calculated fitness scores
    FitnessScores_t fitnessScores =
        initFitnessScores(population->populationSize);

    // Determine initial fitness scores
    fitnessScores = knapsack_populationFitness(population, fitnessScores);
    if (!fitnessScores) {
        free(population);
        return NULL;
    }

    // Main loop of generations
    for (unsigned long generation = 0;
        generation < params.numEvolutions;
        generation++) {

        // SELECTION: Select individuals for reproduction (/"crossover")
        params.selectionFunc();

        // CROSSOVER: Create childs

        // MUTATION: Randomly mutate genes of childs

        // ELITISM: The best individuals survive

        // EVALUTATION: Determine fitness scores of the new population
        fitnessScores = knapsack_populationFitness(population, fitnessScores);
    }

    // Free allocated memory (Fitness array, ...)
    freeFitnessScores(fitnessScores);

    // Returns final population
    return population;
}
