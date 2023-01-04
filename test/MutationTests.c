// Copyright [2021] <Nicola Distl, Hendrik Henselmann>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/Mutation.h"
#include "../include/PopulationInitialization.h"

int main() {

    bool staticIndi[] = {false, false, false, false, false, false};
    Individual_t indi = staticIndi;

    assert(indi[0] == false);
    flipBit(indi, 0);
    assert(indi[0] == true);

    assert(indi[5] == false);
    flipBit(indi, 5);
    assert(indi[5] == true);
    flipBit(indi, 5);
    assert(indi[5] == false);

    return 0;
}
