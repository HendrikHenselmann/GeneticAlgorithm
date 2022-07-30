#include "../../include/Knapsack.h"

#include <stdio.h>
#include <math.h>
#include "limits.h"

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
char separator[] = "===========================================================\
===========";

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
float knapsack_individualFitness(Individual_t individual) {

    // Calculate accumulated weight
    int accWeight = accumulatedIndividualWeight(individual);

    // Check if weight exceeds knapsack cap
    if (accWeight > KNAPSACK_WEIGHT_CAP) { return 0; };

    // Calculate accumulated value
    float accValue = 0;
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        if (individual[i]) {
            accValue += itemList[i].value;
        }
    }
    return accValue;
}

// Calculate the fitness function of the whole population according to the
// problem Writing the fitness into the fitnessArray
FitnessScores_t knapsack_populationFitness(Population_t population) {
    
    // Allocate memory for the FitnessScores_t output struct
    FitnessScores_t fitnessScores =
        createFitnessScores(population->populationSize);

    // Calculate the fitness values
    for (size_t individualIndex = 0;
         individualIndex < population->populationSize;
         individualIndex++) {

        float individualScore = knapsack_individualFitness(
                                    population->array[individualIndex]);
        fitnessScores->array[individualIndex] = individualScore;
    
    }

    return fitnessScores;
}

// Display the problem
void knapsack_displayProblem(void) {
    // Print the heading and a short description
    printf("\n\n%s", separator);
    printf("\nThis is the knapsack problem");
    printf("\n%s", separator);
    printf("\nThere is a predefined set of items and the goal of this game\n"
           "is to select the subset accumulating the greatest value. The accumu\
lated\n"
           "weight of these items is limited by the weight cap of the knapsack."
           );
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
    printf("\n      weight | value");
    printf("\n      -------|------");
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        if (individual[i]){
            printf("\n\t- %02d | %02d", itemList[i].weight, itemList[i].value);
        }
    }

    // Print the accumulated weight and value / fitness
    printf("\n%s", separator);
    printf("\nacc. weight: %03d\t\tacc. value (fitness): %03.2f",
            accumulatedIndividualWeight(individual),
            knapsack_individualFitness(individual));
    printf("\n%s\n\n", separator);

    return;
}

// Calculate the optimal solution fitness
// Returning INT_MIN to indicate failure of malloc
float knapsack_calcOptimum(void) {

    // Initialize an iterating individual
    Individual_t iterationIndi = malloc(NUM_ITEMS * sizeof(bool));
    if (!iterationIndi) return INT_MIN;

    // Initialize a container for the solution candidates value
    float solutionFitness = 0.0f;
    float iterationFitness = 0.0f;

    // Iterate through all possible individuals and check their values
    for (size_t iterInd = 0;
        iterInd < round(pow(2.0, (float) NUM_ITEMS));
        iterInd++) {

        // Set the individual to the binary encoding of the number iterInd
        for (size_t i = 0; i < NUM_ITEMS; i++) {

            // Check if i-th bit is 1
            // Source: https://stackoverflow.com/questions/2249731/how-do-i-get-bit-by-bit-data-from-an-integer-value-in-c
            if (iterInd & ( 1 << i )) {
                iterationIndi[i] = true;
            } else {
                iterationIndi[i] = false;
            }
    
        }

        // Calculate the individual fitness
        iterationFitness = knapsack_individualFitness(iterationIndi);

        // Overwrite the fitness if current individuals fitness exceeds the
        // previous one
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
