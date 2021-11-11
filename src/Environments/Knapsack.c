#include <stdio.h>

#include "../../include/Knapsack.h"

// ----------------------------------------------------------------------------
// Not exportet values and functions
// ----------------------------------------------------------------------------

// Defining the Item List
Item_t itemList[NUM_ITEMS] = {
    {1.0, 1.0},
    {2.0, 2.0}
};

// Defining a seperation line
char seperator[] = "======================================================================";

// Accumulation of individuals weight
float accumulatedIndividualWeight(Individual_t individual) {
    float acc = 0.0;
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        if (individual[i]) {
            acc += itemList[i].weight;
        }
    }
    return acc;
}

// ----------------------------------------------------------------------------

int knapsack_fitness(Individual_t individual) {
    // Calculate accumulated weight
    float accWeight = accumulatedIndividualWeight(individual);
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

void knapsack_displayProblem(void) {
    // Print the heading and a short description
    printf("\n\n%s", seperator);
    printf("\nThis is the knapsack problem");
    printf("\n%s", seperator);
    printf("\nThere is a predefined set of items and the goal of this game\n"
           "is to select the subset accumulating the greatest value. The accumulated\n"
           "weight of these items is limited by the weight cap of the knapsack.");
    printf("\n%s", seperator);

    // Print the set of items
    printf("\nThis is the set of available items:");
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        printf("\n\t-o- %0.2f | %i", itemList[i].weight, itemList[i].value);
    }
    printf("\n%s\n\n", seperator);
    return;
}

void knapsack_displayIndividual(Individual_t individual) {
    // Print the heading
    printf("\n\n%s", seperator);
    printf("\nIndividual:");
    printf("\n%s", seperator);

    // Print the genes / items
    printf("\n\t  weight | value");
    printf("\n\t  -------|------");
    for (size_t i = 0; i < NUM_ITEMS; i++) {
        if (individual[i]){
            printf("\n\t- %3.2f | %i", itemList[i].weight, itemList[i].value);
        }
    }
    printf("\n%s", seperator);

    // Print the accumulated weight and value / fitness
    printf("\n%s", seperator);
    printf("\nacc. weight: %.2f\t\tacc. value (fitness): %i",
            accumulatedIndividualWeight(individual),
            knapsack_fitness(individual));
    printf("\n%s\n\n", seperator);

    return;
}
