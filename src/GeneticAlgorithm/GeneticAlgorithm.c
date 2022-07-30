// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>

#include "../../include/PopulationInitialization.h"

#include "../../include/GeneticAlgorithm.h"

// Running the Genetic Algorithm based on the given parameters
Population_t runGeneticAlgorithm(GAParams_t params) {

    // Initializing population
    Population_t population = initializePopulation(params.populationSize, params.individualSize, 0.5);
    if (!population) {
        return population;
    }

    // Initializing the array of fitness values
    float *fitnessScores = malloc(params.populationSize * sizeof(float));
    if (!fitnessScores) {
        free(population);
        return NULL;
    }

    // Main loop of generations
    for (unsigned long generation = 0; generation < params.numGenerations; generation++) {

        // EVALUTATION: Determine fitness scores 

        // SELECTION: Select individuals for reproduction (crossover)

        // CROSSOVER: Create childs

        // MUTATION: Randomly mutate genes of childs

        // ELITISM: The best individuals survive

    }

    // Free allocated memory (Fitness array, ...)
    free(fitnessScores);

    // Returns final population
    return population;
}
