// Copyright [2023] <Nicola Distl, Hendrik Henselmann>

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/DTypes.h"
#include "../include/Crossover.h"
#include "../include/PopulationInitialization.h"


// ----------------------------------------------------------------------------
    // Defining test function(s)
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
    // Tests of copyIndividualSegment
// ----------------------------------------------------------------------------

    size_t individualSize = 20;
    bool parent0_[20];
    bool parent1_[20];
    bool offspring0_[20];
    memset(parent0_, false, individualSize*sizeof(bool));
    memset(parent1_, true, individualSize*sizeof(bool));
    memset(offspring0_, true, individualSize*sizeof(bool));

    Individual_t parent0 = parent0_;
    Individual_t parent1 = parent1_;
    Individual_t offspring0 = offspring0_;

    // Check if initialization is correct
    for (size_t i = 0; i < individualSize; i++) assert(parent0[i] == false);
    for (size_t i = 0; i < individualSize; i++) assert(parent1[i] == true);
    for (size_t i = 0; i < individualSize; i++) assert(offspring0[i] == true);

    // Copy parent0 to offspring0 | overwriting true by false
    assert(!individualsAreEqual(individualSize, parent0, offspring0));
    copyIndividualSegment (offspring0, parent0, 0, individualSize);
    assert(individualsAreEqual(individualSize, parent0, offspring0));

    // Copy nothing | 0 elements
    assert(!individualsAreEqual(individualSize, parent1, offspring0));
    copyIndividualSegment (offspring0, parent1, 0, 0);
    assert(individualsAreEqual(individualSize, parent0, offspring0));
    assert(!individualsAreEqual(individualSize, parent1, offspring0));

    // Copy first 3 elements
    copyIndividualSegment (offspring0, parent1, 0, 3);
    for (size_t i = 0; i < 3; i++) assert(offspring0[i] == true);
    for (size_t i = 3; i < individualSize; i++) assert(offspring0[i] == false);

    // Reset offspring0
    copyIndividualSegment (offspring0, parent0, 0, individualSize);
    assert(individualsAreEqual(individualSize, parent0, offspring0));

    // Copy 7 elements starting at 5th element
    copyIndividualSegment (offspring0, parent1, 5, 7);
    for (size_t i = 0; i < 5; i++) assert(offspring0[i] == false);
    for (size_t i = 5; i < 12; i++) assert(offspring0[i] == true);
    for (size_t i = 12; i < individualSize; i++) assert(offspring0[i] == false);

    // Reset offspring0
    copyIndividualSegment (offspring0, parent0, 0, individualSize);
    assert(individualsAreEqual(individualSize, parent0, offspring0));

    // Copy 6 elements starting at 14th element
    copyIndividualSegment (offspring0, parent1, 14, individualSize-14);
    for (size_t i = 0; i < 14; i++) assert(offspring0[i] == false);
    for (size_t i = 14; i < individualSize; i++) assert(offspring0[i] == true);

// ----------------------------------------------------------------------------

    return 0;
}
