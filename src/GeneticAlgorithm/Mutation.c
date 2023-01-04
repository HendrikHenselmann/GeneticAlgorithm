// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "../../include/Mutation.h"

// Randomly flip bits of individuals in population
void mutatePopulation(Population_t population, size_t numElitists,
	float probability) {

	for (size_t i = numElitists; i < population->populationSize; i++) {
		mutateIndividual(population->array[i], population->individualSize,
			probability);
	}
	return;
}

// Randomly flip bits of the given individual
void mutateIndividual(Individual_t individual, size_t individualSize,
	float probability) {

	for (size_t i = 0; i < individualSize; i++) {

		size_t randomNumber = rand() % 101;
		if (randomNumber <= probability * 100)
			flipBit (individual, i);

	}
	return;
}

// Flip bit with index bitIndex of given individual
void flipBit (Individual_t individual, size_t bitIndex) {
	individual[bitIndex] = !individual[bitIndex];
	return;
}
