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
    
    // Initializing a struct that stores the indices of selected individuals
    size_t numSelectedPairs =
    ((1-params.elitismRatio) * population->populationSize) / 2; // TODO
    SelectedIndividuals_t selectedIndis =
        initSelectedIndividuals(numSelectedPairs);

    // Add population and fitnessScores as parameters for the Selection and
    // Crossover functions
    params.selectionParams.population = population;
    params.crossoverParams.population = population;
    params.selectionParams.fitnessScores = fitnessScores;

    // Determine initial fitness scores
    fitnessScores = params.populationFitnessFunc(population, fitnessScores);
    if (!fitnessScores) {
        free(population);
        return NULL;
    }

    // Main loop of generations
    for (unsigned long generation = 0;
        generation < params.numEvolutions;
        generation++) {

        // SELECTION: Select individuals for reproduction (/"crossover")
        selectedIndis = params.selectionFunc(params.selectionParams);

        // CROSSOVER: Create childs
        population = params.crossoverFunc(params.crossoverParams);

        // MUTATION: Randomly mutate genes of childs

        // ELITISM: The best individuals survive

        // EVALUTATION: Determine fitness scores of the new population
        fitnessScores = params.populationFitnessFunc(population, fitnessScores);
    }

    // Free allocated memory (Fitness array, ...)
    freeFitnessScores(fitnessScores);
    freeSelectedIndividuals(selectedIndis);

    // Returns final population
    return population;
}
