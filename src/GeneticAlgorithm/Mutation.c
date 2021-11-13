// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../../include/Mutation.h"

void mutate(Individual_t individual, int size_of_individual, float probability) {

  float calc_probability = probability * 100;

  for (int x = 0; x < size_of_individual; x ++) {
    short random_number = rand()%101;
    if (random_number <= calc_probability) {
      individual[x] = !individual[x];
    }
  }
  return;
}