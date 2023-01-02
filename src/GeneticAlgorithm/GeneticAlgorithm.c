// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <string.h>
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

    // Open output files
    FILE *fittestIndiFile = fopen("./logs/00fittestIndividual.txt", "w");
    if (!fittestIndiFile) {
        freeSelectedIndividuals(selectedIndis);
        freeFitnessScores(fitnessScores);
        freePopulation(population);
        return NULL;
    }

    FILE *accumulatedFitnessFile = fopen("./logs/02avgFitness.txt", "w");
    if (!accumulatedFitnessFile) {
        fclose(fittestIndiFile);
        freeSelectedIndividuals(selectedIndis);
        freeFitnessScores(fitnessScores);
        freePopulation(population);
        return NULL;
    }

    FILE *elitistsFitnessFile = fopen("./logs/01elitistsAvgFitness.txt", "w");
    if (!elitistsFitnessFile) {
        fclose(accumulatedFitnessFile);
        fclose(fittestIndiFile);
        freeSelectedIndividuals(selectedIndis);
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

        // Sum fitness scores and write them to files
        float accFitness = 0;
        float accElitistsFitness = 0;
        for (size_t i = 0; i < fitnessScores->size; i++)
        {
            accFitness += fitnessScores->array[i];
            if (i < numElitists) accElitistsFitness += fitnessScores->array[i];
        }
        fprintf(fittestIndiFile, "%.3f\n", fitnessScores->array[0]);
        fprintf(accumulatedFitnessFile, "%.3f\n",
            accFitness / population->populationSize);
        fprintf(elitistsFitnessFile, "%.3f\n",
            accElitistsFitness / numElitists);

        // Print intermediate fitness scores depending on verbosity level
        if (params.verbosityLevel == 3)
            printFitnessScores(fitnessScores);
        else if (params.verbosityLevel == 2) {
            printf("Max fitness: %.03f | acc. fitness: %.03f\n",
                fitnessScores->array[0], accFitness);
        } else if (params.verbosityLevel == 1)
            printf("Max fitness: %.03f\n", fitnessScores->array[0]);
        else if (params.verbosityLevel == 0)
        {
            // Print a progress bar
            size_t barWidth = 10;
            size_t progress =
                round(
                    ((float) barWidth * (float) (generation + 1))
                    / (float) params.numEvolutions
                );
            printf("\rProgress: [");
            for (int _ = 0; _ < progress; _++) printf("\u2593");
            for (int _ = progress; _ < barWidth; _++)
                printf("\u2591");
            printf("]\tGeneration: [%zu/%zu]",
                generation+1, params.numEvolutions);
        }

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

    // Sort fitness scores
    applyElitism(population, fitnessScores);

    // Print final fitness scores
    // Note that they are not sorted at this point
    printf("\n\n\nFinal fitness: ");
    printFitnessScores(fitnessScores);

    // Display the fittest individual
    printf("\n\nFinal Solution:\n");
    params.env.displayIndividual(population->array[0]);

    // Sum fitness scores and write them to files
    float accFitness = 0;
    float accElitistsFitness = 0;
    for (size_t i = 0; i < fitnessScores->size; i++)
    {
        accFitness += fitnessScores->array[i];
        if (i < numElitists) accElitistsFitness += fitnessScores->array[i];
    }
    fprintf(fittestIndiFile, "%.3f\n", fitnessScores->array[0]);
    fprintf(accumulatedFitnessFile, "%.3f\n",
        accFitness / population->populationSize);
    fprintf(elitistsFitnessFile, "%.3f\n",
        accElitistsFitness / numElitists);

    // Free allocated memory (Fitness array, ...)
    freeSelectedIndividuals(selectedIndis);
    freeFitnessScores(fitnessScores);

    // Close output files
    fclose(elitistsFitnessFile);
    fclose(accumulatedFitnessFile);
    fclose(fittestIndiFile);

    // Returns final population
    return population;
}
