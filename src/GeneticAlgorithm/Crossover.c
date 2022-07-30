// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include "../../include/Crossover.h"

CrossoverParams_t initOnePointCrossoverParams(Population_t population, 
    SelectedIndividuals_t selectedIndividuals) {

    return (CrossoverParams_t) {
        .population = population,
        .selectedIndividuals = selectedIndividuals
    };
}

CrossoverParams_t initTwoPointCrossoverParams(Population_t population, 
    SelectedIndividuals_t selectedIndividuals) {
    
    return (CrossoverParams_t) {
        .population = population,
        .selectedIndividuals = selectedIndividuals
    };
}

SelectedIndividuals_t onePointCrossover(
    SelectedIndividuals_t selectedIndividuals) {
    // TODO
    return NULL;
}

SelectedIndividuals_t twoPointCrossover(
    SelectedIndividuals_t selectedIndividuals) {
    // TODO
    return NULL;
}
