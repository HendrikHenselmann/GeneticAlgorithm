// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include "../../include/EightQueens.h"

#include <stdio.h>

// Defining a seperation line
static char separator[] = "=====================================================\
=================";

// Calculate the fitness function of an individual according to the problem
// Counting the number of conflicting queens, the lesse the better
float eightQueens_individualFitness (Individual_t individual) {

    // Set num conflicts to the max number possible
    unsigned numConflicts = 28; //4*7 = 28

    // Initialize conflict counters for columns/rows/diagonals
    unsigned xs[8] = {0};
    unsigned ys[8] = {0};
    unsigned z1s[15] = {0};
    unsigned z2s[15] = {0};

    // Convert the bit patterns to the (x, y) coordinate of the queens
    // Then increment the number of conflicts per
    // column/row/diagonal1/diagonal2
    for (unsigned queenID = 0; queenID < 8; queenID++) {

        // Extracting (x, y) coordinate of the current queen
        unsigned xCoord = 0;
        for (unsigned i = 0; i < 3; i++)
            if (individual[6*queenID + i])
                xCoord += 1 << i;

        unsigned yCoord = 0;
        for (unsigned i = 0; i < 3; i++)
            if (individual[6*queenID + 3 + i])
                yCoord += 1 << i;

        // Calculate the group memberships of the current queen
        xs[xCoord]++;
        ys[yCoord]++;
        z1s[xCoord+yCoord]++;
        z2s[7-xCoord+yCoord]++;
    }

    // Subtract the number of conflicts
    for (unsigned i = 0; i < 8; i++)
        if (xs[i] > 0)
            numConflicts -= xs[i] - 1;
    for (unsigned i = 0; i < 8; i++)
        if (ys[i] > 0)
            numConflicts -= ys[i] - 1;
    for (unsigned i = 0; i < 15; i++)
        if (z1s[i] > 0)
            numConflicts -= z1s[i] - 1;
    for (unsigned i = 0; i < 15; i++)
        if (z2s[i] > 0)
            numConflicts -= z2s[i] - 1;

    return (float) numConflicts;
}

// Calculate the fitness function of the whole population according to the
// problem. Writing the fitness into the fitnessScores struct.
void eightQueens_populationFitness (Population_t population,
    FitnessScores_t fitnessScores) {
    for (size_t indi = 0; indi < population->populationSize; indi++) {
        fitnessScores->array[indi] =
            eightQueens_individualFitness (population->array[indi]);
    }
}

// Display the problem
void eightQueens_displayProblem (void) {
    // Print the heading and a short description
    printf("\n\n%s", separator);
    printf("\nThis is the 8 Queens problem");
    printf("\n%s", separator);
    printf("\nThe goal is to place 8 queens on an 8x8 tiled chess board.\n"
    "There cannot be any conflicts emerging from the attack pattern\n"
    "of classic chess."
    );
    printf("\n%s\n\n", separator);
    return;
}

// Helper function for eightQueens_displayIndividual
void printBoardSeperator (void) {
    printf("\n\t");
    for (int _ = 0; _ < 8; _++) printf("|---");
    printf("|\n");
}

// Display an Individual interpreted according to the problem
void eightQueens_displayIndividual (Individual_t individual) {

    // Print the heading
    printf("\n\n%s", separator);
    printf("\nIndividual:");
    printf("\n%s\n\n", separator);

    // Extract board out of individuals representation
    bool board[64] = {false};

    // Insert every queen into board
    for (unsigned queenID = 0; queenID < 8; queenID++) {

        // Extracting (x, y) coordinate of the current queen
        unsigned xCoord = 0;
        for (unsigned i = 0; i < 3; i++) if (individual[6*queenID + i])
            xCoord += 1 << i;

        unsigned yCoord = 0;
        for (unsigned i = 0; i < 3; i++) if (individual[6*queenID + 3 + i])
            yCoord += 1 << i;

        // Insert into board
        board[xCoord + 8*yCoord] = true;
    }

    // Print the chess board that is represented by the genes
    printBoardSeperator ();
    for (unsigned y = 0; y < 8; y++) {
        printf("\t");
        for (unsigned x = 0; x < 8; x++) {
            printf("| ");
            if (board[x+8*y]) printf("x"); else printf(" ");
            printf(" ");
        }
        printf("|");
        printBoardSeperator ();
    }

    // Print the number of conflicts (fitness value)
    printf("\n%s", separator);
    float indiFitness = eightQueens_individualFitness(individual);
    printf("\nconflicts: %02.f of 28, fitness: %02.f",
        28 - indiFitness,
        indiFitness
        );
    printf("\n%s\n\n", separator);

    return;
}

// Assembling the environment
Environment_t eightQueensProblem = (Environment_t) {
    .individualSize = 48,  // (x, y) coordinates of 8 Queens, x and y in [0, 7] encoded by 3 bit => 8 * 2 * 3 = 48
    .geneLength = 3,  // 3 bools encode one coordinate
    .displayProblem = eightQueens_displayProblem,
    .displayIndividual = eightQueens_displayIndividual,
    .calcIndividualFitness = eightQueens_individualFitness,
    .calcPopulationFitness = eightQueens_populationFitness};
