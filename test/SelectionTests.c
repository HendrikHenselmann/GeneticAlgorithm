// Copyright [2023] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>
#include <assert.h>

#include "../include/DTypes.h"
#include "../include/Selection.h"
#include "../include/PopulationInitialization.h"


// ----------------------------------------------------------------------------
    // Defining a test function
// ----------------------------------------------------------------------------

    bool individualsAreEqual (size_t individualSize,
        Individual_t indi1, Individual_t indi2) {
        for (size_t i = 0; i < individualSize; i++)
            if (indi1[i] != indi2[i])
                return false;
        return true;
    }

// ----------------------------------------------------------------------------


int main() {

// ----------------------------------------------------------------------------
    // Define Individuals / Population for tests
// ----------------------------------------------------------------------------

    Population_t population = initializePopulation (20, 20, 0.0);
    if (!population) return -1;
    SelectedIndividuals_t selectedIndis = initSelectedIndividuals (10, 20);
    if (!selectedIndis) {
        freePopulation (population);
        return -1;
    }

    // Reinitialize population such that any two individuals are different
    for (size_t i = 0; i < population->populationSize; i++) {
        for (size_t j = 0; j < population->individualSize; j++) {
            Individual_t indi = population->array[i];
            indi[j] = (j < i) ? true : false; 
        }
    }

// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
    // Tests if initialization assumption is holding
// ----------------------------------------------------------------------------

    for (size_t i = 0; i < population->populationSize; i++)
        for (size_t j = 0; j < population->populationSize; j++) {
            Individual_t indi1 = population->array[i];
            Individual_t indi2 = population->array[j];
            if (i != j) 
                assert(
                    !individualsAreEqual (population->individualSize,
                        indi1,indi2)
                );
        }

// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
    // Tests of copySelectedParents
// ----------------------------------------------------------------------------

    // Select the whole population, basically copying it
    for (size_t i = 0; i < population->populationSize / 2; i++) {
        copySelectedParents(population, selectedIndis, i, 2*i, 2*i+1);
    }

    // Check whether it is an exact copy
    for (size_t i = 0; i < population->populationSize; i++) {
        Individual_t parent = population->array[i];
        Individual_t selected = selectedIndis->array[i];
        assert (
            individualsAreEqual (population->individualSize, parent, selected)
        );
    }

// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
    // Free all memory allocations
// ----------------------------------------------------------------------------

    freeSelectedIndividuals (selectedIndis);
    freePopulation (population);

// ----------------------------------------------------------------------------

    return 0;
}
