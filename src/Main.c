// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include <time.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/Knapsack.h"
#include "../include/EightQueens.h"

#include "../include/Selection.h"
#include "../include/Crossover.h"
// #include "../include/Mutation.h"
#include "../include/GeneticAlgorithm.h"
#include "../include/PopulationInitialization.h"

#define DEFAULT_NUM_EVOLUTIONS 1000
#define DEFAULT_POPULATION_SIZE 20
#define DEFAULT_MUTATION_RATE 0.1
#define DEFAULT_ELITISM_RATIO 0.2
#define DEFAULT_ACTIVE_GENE_RATE 0.5
#define DEFAULT_VERBOSITY_LEVEL 0

void printHelpText (void) {
    printf("\nArgument | Default");
    printf("\n=======================================");
    printf("\nNumber of evolutions | %d", DEFAULT_NUM_EVOLUTIONS);
    printf("\nPopulation size | %d", DEFAULT_POPULATION_SIZE);
    printf("\nMutation rate | %.3f", DEFAULT_MUTATION_RATE);
    printf("\nElitism ratio | %.3f", DEFAULT_ELITISM_RATIO);
    printf("\nActive gene rate at initialization | %.3f", DEFAULT_ACTIVE_GENE_RATE);
    printf("\nVerbosity level | %d", DEFAULT_VERBOSITY_LEVEL);
    printf("\n\n");
    return;
}

// Determine if a float is a valid probability value in [0, 1]
bool floatIsProba (float f) {
    return (f > 0.0 - FLT_EPSILON) && (f < 1.0 + FLT_EPSILON);
}

int main(int argc, char *argv[]) {

    // Set random seed. This should be done once for the the whole program!
    // It is very important that this is the only place where srand is called!
    srand(time(NULL));

    // Command line argument parsing
    if (argc > 1
        && (strcmp (argv[1], "-h") == 0
            || strcmp (argv[1], "--help") == 0)) {
        printHelpText ();
        return 0;
    }
    unsigned long numEvolutions = DEFAULT_NUM_EVOLUTIONS;
    if (argc > 1) numEvolutions = atoi(argv[1]);
    size_t populationSize = DEFAULT_POPULATION_SIZE;
    if (argc > 2) populationSize = atoi(argv[2]);
    float mutationProbability = DEFAULT_MUTATION_RATE;
    if (argc > 3) mutationProbability = atof(argv[3]);
    float elitismRatio = DEFAULT_ELITISM_RATIO;
    if (argc > 4) elitismRatio = atof(argv[4]);
    float activeGeneRate = DEFAULT_ACTIVE_GENE_RATE;
    if (argc > 5) activeGeneRate = atof(argv[5]);
    int verbosityLevel = DEFAULT_VERBOSITY_LEVEL;
    if (argc > 6) verbosityLevel = atoi(argv[6]);

    // Check if user input is valid
    assert (numEvolutions > 0);
    assert (populationSize > 0);
    assert (floatIsProba (mutationProbability));
    assert (floatIsProba (elitismRatio));
    assert (floatIsProba (activeGeneRate));
    assert (verbosityLevel >= 0 && verbosityLevel <= 3);

    // Choosing the problem
    Environment_t env = eightQueensProblem;

    // Display Problem
    env.displayProblem();

    // Define parameters of the genetic algorithm
    SelectionParams_t selectionParams = initRouletteSelectionParams();
    CrossoverParams_t crossoverParams = initOnePointCrossoverParams();

    GAParams_t gaParams = initGAParams(
        env, // Environment
        populationSize, // Size of population
        activeGeneRate, // Active gene rate at population initialization
        numEvolutions, // Number of generations
        elitismRatio, // Elitism ratio
        mutationProbability, // Mutation rate
        selectionParams,
        rouletteSelection, // Selection function
        crossoverParams,
        twoPointCrossover, // Crossover function
        verbosityLevel // Verbosity
    );

    // Run the Genetic Algorithm
    Population_t finalPopulation = runGeneticAlgorithm(gaParams);

    // Free all memory allocations
    freePopulation(finalPopulation);

    return 0;
}
