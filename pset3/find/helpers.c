/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
#define SWAP(A, B) { int t = A; A = B; B = t; }
#include <cs50.h>
#include <math.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n) {
    if (n < 0) {
        return false;
    }

    int index = n/2;
    int temp = 2;
    while (values[index] != value){
        if (round((float) n/(temp)) == 1){
            return false;
        }
        if (values[index] > value){
            index -= round((float) n/(2*temp));
        } else {
            index += round((float) n/(2*temp));
        }
        temp *= 2;
    }

    return true;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n) {
	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j < n; j++){
			if (values[i] > values[j]){
				SWAP(values[i], values[j]);
			}
		}
	}
}