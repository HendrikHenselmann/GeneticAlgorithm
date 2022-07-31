// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include "../../include/Crossover.h"

CrossoverParams_t initOnePointCrossoverParams(void) {

    return (CrossoverParams_t) {};
}

CrossoverParams_t initTwoPointCrossoverParams(void) {
    
    return (CrossoverParams_t) {};
}

Population_t onePointCrossover(CrossoverParams_t params) {
    // TODO
    return params.population;
}

Population_t twoPointCrossover(CrossoverParams_t params) {
    // TODO
    return params.population;
}
