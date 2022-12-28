// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../include/Elitism.h"
#include "../../include/Mutation.h"
#include "../../include/Knapsack.h"
#include "../../include/PopulationInitialization.h"

#include "../../include/GeneticAlgorithm.h"

// Assembling the Genetic Algorithm parameters
GAParams_t initGAParams(Environment_t env, size_t populationSize,
    float activeGeneRate, unsigned long numEvolutions, float elitismRatio,
    float mutationProbability,
    SelectionParams_t selectionParams,
    void (*selectionFunc) (SelectionParams_t params),
    CrossoverParams_t crossoverParams,
    void (*crossoverFunc) (CrossoverParams_t params),
    int verbosityLevel) {

    return (GAParams_t) {
        .env = env,
        .populationSize = populationSize,
        .activeGeneRate = activeGeneRate,
        .numEvolutions = numEvolutions,
        .elitismRatio = elitismRatio,
        .mutationProbability = mutationProbability,
        .selectionParams = selectionParams,
        .selectionFunc = selectionFunc,
        .crossoverParams = crossoverParams,
        .crossoverFunc = crossoverFunc,
        .verbosityLevel = verbosityLevel
    };
}

// Running the Genetic Algorithm based on the given parameters
Population_t runGeneticAlgorithm(GAParams_t params) {

    // Determine the number of individuals that have to be selected by the
    // Selection function for every evolution step.
    size_t numElitists =
        round(params.elitismRatio * params.populationSize);
    size_t numSelectedIndividuals = params.populationSize - numElitists;

    // Make sure that the amount of selected individuals is even,
    // to be able to successfully apply the crossover function.
    size_t numSelectedPairs = numSelectedIndividuals / 2;
    if (numSelectedIndividuals % 2 != 0) {
        numSelectedPairs = (numSelectedIndividuals+1) / 2;
        numElitists--;
    }

    // Initializing population
    Population_t population =
        initializePopulation(params.populationSize, params.env.individualSize,
            params.activeGeneRate);
    if (!population) {
        return NULL;
    }

    // Initializing a struct that stores calculated fitness scores
    FitnessScores_t fitnessScores =
        initFitnessScores(population->populationSize);
    if (!fitnessScores) {
        freePopulation(population);
        return NULL;
    }

    // Initializing a struct that stores the indices of selected individuals
    SelectedIndividuals_t selectedIndis =
        initSelectedIndividuals(numSelectedPairs, params.env.individualSize);
    if (!selectedIndis) {
        freeFitnessScores(fitnessScores);
        freePopulation(population);
        return NULL;
    }

// -----------------------------------------------------------------------------
    // Setup of function parameters.
    // This is a very important step since a forgotten parameter here can cause
    // segmentation faults and other bugs!
    // Add population, numSelectedPairs, fitnessScores etc. as parameters of the
    // Selection and Crossover functions.
// -----------------------------------------------------------------------------

    // Setup selection function parameters
    params.selectionParams.population = population;
    params.selectionParams.numSelectedPairs = numSelectedPairs;
    params.selectionParams.selectedIndividuals = selectedIndis;
    params.selectionParams.fitnessScores = fitnessScores;

    // Setup crossover function parameters
    params.crossoverParams.numElitists = numElitists;
    params.crossoverParams.population = population;
    params.crossoverParams.selectedIndividuals = selectedIndis;
    params.crossoverParams.geneLength = params.env.geneLength;

// -----------------------------------------------------------------------------

    printf("GA initialization successfull!\n");

    // Determine initial fitness scores
    params.env.calcPopulationFitness(population, fitnessScores);

    // Main loop of generations
    for (unsigned long generation = 0;
        generation < params.numEvolutions;
        generation++) {

        // ELITISM: The fittest individuals survive unmodified.
        applyElitism(population, fitnessScores);

        // Print intermediate fitness scores depending on verbosity level
        if (params.verbosityLevel == 3)
            printFitnessScores(fitnessScores);
        else if (params.verbosityLevel == 2) {
            float accFitness = 0;
            for (size_t i = 0; i < fitnessScores->size; i++)
                accFitness += fitnessScores->array[i];
            printf("Max fitness: %.03f | acc. fitness: %.03f\n",
                fitnessScores->array[0], accFitness);
        } else if (params.verbosityLevel == 1)
            printf("Max fitness: %.03f\n", fitnessScores->array[0]);

        // SELECTION: Select individuals for reproduction (/"crossover")
        params.selectionFunc(params.selectionParams);

        // CROSSOVER: Create childs
        params.crossoverFunc(params.crossoverParams);

        // MUTATION: Randomly mutate genes of childs
        // TODO: Standardize so that this line will be:
        // params.mutationFunc(params.mutationParams);
        mutatePopulation(population, numElitists, params.mutationProbability);

        // EVALUTATION: Determine fitness scores of the new population
        params.env.calcPopulationFitness(population, fitnessScores);

    }

    // Print final fitness scores
    printf("Final fitness: ");
    printFitnessScores(fitnessScores);

    // Display the fittest individual
    printf("\n\nFinal Solution:\n");
    size_t fittest = fittestIndividual(fitnessScores);
    params.env.displayIndividual(population->array[fittest]);

    // Free allocated memory (Fitness array, ...)
    freeSelectedIndividuals(selectedIndis);
    freeFitnessScores(fitnessScores);

    // Returns final population
    return population;
}
