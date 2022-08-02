// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Knapsack.h"
#include "../include/Selection.h"
#include "../include/Crossover.h"
// #include "../include/Mutation.h"
#include "../include/GeneticAlgorithm.h"
#include "../include/PopulationInitialization.h"

int main() {
    
    // Set random seed. This should be done once for the the whole program!
    // It is very important that this is the only place where srand is called!
    srand(time(NULL));

    // Display Problem
    knapsack_displayProblem();

    // Define parameters of the genetic algorithm
    SelectionParams_t selectionParams = initRandomSelectionParams();
    CrossoverParams_t crossoverParams = initOnePointCrossoverParams();

    GAParams_t gaParams = initGAParams(
        NUM_ITEMS, // Size of individual
        15, // Size of population
        0.2, // Active gene rate at population initialization
        40, // Number of generations
        0.3, // Elitism ratio 
        0.3, // Mutation rate
        selectionParams,
        rouletteSelection, // Selection function
        crossoverParams,
        onePointCrossover, // Crossover function
        knapsack_populationFitness // Fitness function
    );

    // Run the Genetic Algorithm
    Population_t finalPopulation = runGeneticAlgorithm(gaParams);

    // Free all memory allocations
    freePopulation(finalPopulation);

    return 0;
}
