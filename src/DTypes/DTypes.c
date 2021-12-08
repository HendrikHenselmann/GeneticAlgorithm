#include "../../include/DTypes.h"

void printIndividual(Individual_t individual, size_t individualSize) {
    printf("Individual:\n===========\n");
    for (size_t i = 0; i < individualSize; i++) {
        printf("%d", individual[i]);
    }
    printf("\n");
}

void printPopulation(Population_t population) {
    char separator[] = "======================================================================";
    printf("Population:\n");
    printf("%s\n", separator);
    for (size_t indiIndex = 0; indiIndex < population.populationSize; indiIndex++) {
        for (size_t i = 0; i < population.individualSize; i++) {
        printf("%d", population.array[indiIndex][i]);
        }
        printf("\n");
    }
    printf("%s\n", separator);
}
