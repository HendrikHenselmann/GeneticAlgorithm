// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../include/PopulationInitialization.h"

#include "../../include/GeneticAlgorithm.h"

// Assembling the Genetic Algorithm parameters
GAParams_t initGAParams(size_t individualSize, size_t populationSize,
    unsigned long numEvolutions, float elitismRatio, float mutationProbability,
    SelectionParams_t selectionParams,
    SelectedIndividuals_t (*selectionFunc) (SelectionParams_t params),
    CrossoverParams_t crossoverParams,
    Population_t (*crossoverFunc) (CrossoverParams_t params),
    FitnessScores_t (*populationFitnessFunc) (Population_t population,
        FitnessScores_t fitnessScores)
    ) {

    return (GAParams_t) {
        .individualSize = individualSize,
        .populationSize = populationSize,
        .numEvolutions = numEvolutions,
        .elitismRatio = elitismRatio,
        .mutationProbability = mutationProbability,
        .selectionParams = selectionParams,
        .selectionFunc = selectionFunc,
        .crossoverParams = crossoverParams,
        .crossoverFunc = crossoverFunc,
        .populationFitnessFunc = populationFitnessFunc
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
        initializePopulation(params.populationSize, params.individualSize, 0.5);
    if (!population) {
        return NULL;
    }

    // Initializing a struct that stores calculated fitness scores
    FitnessScores_t fitnessScores =
        initFitnessScores(population->populationSize);

    // Initializing a struct that stores the indices of selected individuals
    SelectedIndividuals_t selectedIndis =
        initSelectedIndividuals(numSelectedPairs);

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

// -----------------------------------------------------------------------------

    printf("GA initialization successfull!\n");

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

        // EVALUTATION: Determine fitness scores of the new population
        fitnessScores = params.populationFitnessFunc(population, fitnessScores);
    }

    // Free allocated memory (Fitness array, ...)
    freeFitnessScores(fitnessScores);
    freeSelectedIndividuals(selectedIndis);

    // Returns final population
    return population;
}
