// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>

#include "../../include/PopulationInitialization.h"

// Initializing a random individual
// Returning null pointer if error occures, else a random individual
Individual_t initializeIndividual(size_t individualSize,
                                  float activeGeneProba) {

    // Allocate memory for the boolean vector
    Individual_t individual = malloc(sizeof(bool) * individualSize);
    if (!individual) {
        return individual;
    }

    // Insert random bits
    for (size_t i = 0; i < individualSize; i++) {
        individual[i] = rand() % 100 <= 100*activeGeneProba;
    }

    return individual;
}

// Initializing a random population
// activeGeneProba is the probability that an individuals gene is 1
// Returning NullPointer if some error occures, else the initialized random
// population
Population_t initializePopulation(size_t populationSize, size_t individualSize,
    float activeGeneProba) {

    // Initializing memory for the population struct
    Population_t population = malloc(sizeof(struct Population_));
    if (!population) {
        return population;
    }

    // Initializing the array of Individuals
    Individual_t *arrayOfIndividuals =
        malloc(sizeof(Individual_t) * populationSize);
    if (!arrayOfIndividuals) {
        free(population);
        return NULL;
    }

    // Initializing the individuals randomly
    for (size_t i = 0; i < populationSize; i++) {

        // Create a random Individual
        Individual_t randomIndividual =
            initializeIndividual(individualSize, activeGeneProba);
        
        // If an error occures -> Free all the allocated memory
        if (!randomIndividual) {

            // Loop through the already allocated pointers
            for (size_t j = 0; j < i; j++) {
                free(arrayOfIndividuals[j]);
            }
            free(population);
            free(arrayOfIndividuals);
            return NULL;
        }

        arrayOfIndividuals[i] = randomIndividual;

    }

    // Fill the struct
    population->populationSize = populationSize;
    population->individualSize = individualSize;
    population->array = arrayOfIndividuals;

    return population;
}
