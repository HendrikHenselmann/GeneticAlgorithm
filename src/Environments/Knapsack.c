#include <stdio.h>
#include <math.h>

#include "../../include/Knapsack.h"

// ----------------------------------------------------------------------------
// Not exportet values and functions
// ----------------------------------------------------------------------------

// Defining the Item List
Item_t itemList[NUM_ITEMS] = {
    {4, 19},
    {24, 12},  
    {32, 10},
    {53, 32},
    {12, 10},
    {63, 37},
    {35, 28},
    {12, 8},
    {44, 36},
    {70, 61}
};

// Defining a seperation line
char separator[] = "======================================================================";

// Accumulation of individuals weight
int accumulatedIndividualWeight(Individual_t individual) {
    int acc = 0;
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        if (individual[i]) {
            acc += itemList[i].weight;
        }
    }
    return acc;
}


// ----------------------------------------------------------------------------
// Calculate the fitness function of an individual according to the problem
int knapsack_fitness(Individual_t individual) {
    // Calculate accumulated weight
    int accWeight = accumulatedIndividualWeight(individual);
    // Check if weight exceeds knapsack cap
    if (accWeight > KNAPSACK_WEIGHT_CAP) { return 0; };

    // Calculate accumulated value
    int accValue = 0;
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        if (individual[i]) {
            accValue += itemList[i].value;
        }
    }
    return accValue;
}

// Display the problem
void knapsack_displayProblem(void) {
    // Print the heading and a short description
    printf("\n\n%s", separator);
    printf("\nThis is the knapsack problem");
    printf("\n%s", separator);
    printf("\nThere is a predefined set of items and the goal of this game\n"
           "is to select the subset accumulating the greatest value. The accumulated\n"
           "weight of these items is limited by the weight cap of the knapsack.");
    printf("\n%s", separator);

    // Print the set of items
    printf("\nThis is the set of available items:");
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        printf("\n\t-o- %02d | %02d", itemList[i].weight, itemList[i].value);
    }
    printf("\n%s\n\n", separator);
    return;
}

// Display an Individual interpreted according to the problem
void knapsack_displayIndividual(Individual_t individual) {
    // Print the heading
    printf("\n\n%s", separator);
    printf("\nIndividual:");
    printf("\n%s", separator);

    // Print the genes / items
    printf("\n      weight | value");
    printf("\n      -------|------");
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        if (individual[i]){
            printf("\n\t- %02d | %02d", itemList[i].weight, itemList[i].value);
        }
    }

    // Print the accumulated weight and value / fitness
    printf("\n%s", separator);
    printf("\nacc. weight: %03d\t\tacc. value (fitness): %03d",
            accumulatedIndividualWeight(individual),
            knapsack_fitness(individual));
    printf("\n%s\n\n", separator);

    return;
}

// Calculate the optimal solution fitness
int knapsack_calcOptimum(void) {
    // Initialize an iterating individual
    Individual_t iterationIndi = malloc(NUM_ITEMS * sizeof(bool));

    // Initialize a container for the solution candidates value
    int solutionFitness = 0;
    int iterationFitness = 0;

    // Iterate through all possible individuals and check their values
    for (size_t iterInd = 0; iterInd < round(pow(2.0, (float) NUM_ITEMS)); iterInd++) {

        // Set the individual to the binary encoding of the number iterInd
        for (size_t i = 0; i < NUM_ITEMS; i++) {

            // Source: https://stackoverflow.com/questions/2249731/how-do-i-get-bit-by-bit-data-from-an-integer-value-in-c
            if ((iterInd & ( 1 << i )) >> i) {
                iterationIndi[i] = true;
            }
        }

        // Calculate the individual fitness
        iterationFitness = knapsack_fitness(iterationIndi);

        // Overwrite the fitness if current individuals fitness exceeds the previous one
        if (iterationFitness > solutionFitness) {
            // Overwrite fitness
            solutionFitness = iterationFitness;
        }
    }

    // Free memory
    free(iterationIndi);

    // Return optimal fitness
    return solutionFitness;
}
