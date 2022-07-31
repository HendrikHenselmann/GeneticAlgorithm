// Copyright [2022] <Nicola Distl, Hendrik Henselmann>

#include <math.h>

#include "../../include/Elitism.h"

size_t quicksortDivide(Population_t population, FitnessScores_t fitnessScores,
    size_t left, size_t right) {
    
    // Select pivot element
    size_t pivotID = right;
    size_t pivot = fitnessScores->array[pivotID];

    // Ids to scan section from the left (i) and from the right (j)
    size_t i = left;
    size_t j = right-1;

    // Terminating the scan process when the pointers meet in the middle
    while (i < j) {

        // Scan from left until an element is found that is not larger than the
        // pivot element.
        // Furthermore terminating if the whole array was scanned.
        while ( i < j
            && fitnessScores->array[i] > pivot )
            i++;
        
        // Scan from right until a larger element than pivot is found.
        // Furthermore terminating if the whole array was scanned.
        while ( j > i
            && fitnessScores->array[j] <= pivot )
            j--;

        if (fitnessScores->array[i] > fitnessScores->array[j]) continue;
    
        // Swap the two elements that were found to be in wrong 'order'. Wrong
        // order' in the sense of larger or equal on the left of the final pivot
        // location and smaller on the right of the final pivot location.
        float tempFitness = fitnessScores->array[i];
        fitnessScores->array[i] = fitnessScores->array[j];
        fitnessScores->array[j] = tempFitness;

        Individual_t tempIndividual = population->array[i];
        population->array[i] = population->array[j];
        population->array[j] = tempIndividual;

    }

    // Decide wether the pivot element has to be moved or if it can stay
    // at its initial position.
    if (fitnessScores->array[i] < pivot) {

        // After the whole array is 'ordered', assign pivot element to its
        // calculated final destination
        fitnessScores->array[pivotID] = fitnessScores->array[i];
        fitnessScores->array[i] = pivot;

        Individual_t tempIndividual = population->array[pivotID];
        population->array[pivotID] = population->array[i];
        population->array[i] = tempIndividual;

    } else { // Don't swap cause the element ith is equal to pivot element
        i = right;
    }

    // Return the final position of the pivot element
    return i;
}

// Doing an inplace sorting of population according to fitnessScores.
// Sorting in decending order.
void quicksort(Population_t population, FitnessScores_t fitnessScores,
    long left, long right) {

    if (left >= right) return;

    size_t pivotID = quicksortDivide(population, fitnessScores, left, right);
    quicksort(population, fitnessScores, left, pivotID-1);
    quicksort(population, fitnessScores, pivotID+1, right);

}

// Restructuring the population so that the first {numElitists} individuals of
// the population are the fittest individuals. They will survive unmodified.
// Restructuring the fitness score array accordingly.
// This is achieved by inplace sorting. O(n*log n)
void applyElitism(Population_t population, FitnessScores_t fitnessScores) {
    
    quicksort(population, fitnessScores, 0, population->populationSize-1);

}
