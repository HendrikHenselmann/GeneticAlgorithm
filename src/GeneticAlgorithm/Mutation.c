// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../../include/Mutation.h"

void mutate_population(Population_t *population, int size_of_individual, int size_of_population) {
  Population_t *temp_population;
  temp_population = malloc(sizeof(bool) * size_of_individual * size_of_population);
  printf("temp population size %lu", sizeof(temp_population));

  for (int x = 0; x < size_of_population; x ++) {
    mutate_individual(population[x], size_of_individual, 0.5);
  }
}

void mutate_individual(Individual_t individual, int size_of_individual, float probability) {

  float calc_probability = probability * 100;

  for (int x = 0; x < size_of_individual; x ++) {
    short random_number = rand()%101;
    if (random_number <= calc_probability) {
      individual[x] = !individual[x];
    }
  }
  return;
}
