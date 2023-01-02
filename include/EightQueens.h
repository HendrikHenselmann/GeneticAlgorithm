// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#ifndef EIGHTQUEENS_H_
#define EIGHTQUEENS_H_

// ----------------------------------------------------------------------------
// Imports
// ----------------------------------------------------------------------------
// Project headers
#include "./DTypes.h"
#include "./Environment.h"
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Functions
// ----------------------------------------------------------------------------
// Calculate the fitness function of an individual according to the problem
float eightQueens_individualFitness (Individual_t individual);
// Calculate the fitness function of the whole population according to the
// problem. Writing the fitness into the fitnessScores struct.
void eightQueens_populationFitness (Population_t population,
    FitnessScores_t fitnessScores);
// Display the problem
void eightQueens_displayProblem(void);
// Display an Individual interpreted according to the problem
void eightQueens_displayIndividual (Individual_t individual);
// Display the Population interpreted according to the problem
void eightQueens_displayPopulation (Population_t population);
// Calculate the optimal solution
// Returning INT_MIN to indicate failure of malloc
float eightQueens_calcOptimum (void);
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// The exported environment
// ----------------------------------------------------------------------------
Environment_t eightQueensProblem;
// ----------------------------------------------------------------------------

#endif  // EIGHTQUEENS_H_
