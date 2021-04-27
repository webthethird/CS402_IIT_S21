/*
 * basicstats.c
 *
 *  Created on: Apr 25, 2021
 *  	   For: CS 402, Spring '21 @ IIT
 *      Author: William E Bodell III
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "readfile.h"

/* Define ANSI tags for printing in color */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* Declare method interfaces from below */
void load_data(float*, int);
void print_results(float*, int, int);
float* enlarge_array(float*, int);
int float_comparator(const void*, const void*);
float compute_mean(float*, int);
float compute_median(float*, int);
float compute_stddev(float*, int);

/*
 * Main:
 *
 * Attempts to open the file located at the filepath
 * provided in the command line arguments.
 *
 * If successful, sets the initial max array size to 20 and
 * allocates space in memory for an array of 20 floats before
 * calling load_data.
 *
 * argc - unused
 * argv - holds the filename input by the user at launch
 * returns -1 on error opening file, 0 otherwise
 */
int main(int argc, const char *argv[]) {
	if (open_file(argv[1]) == -1)
	{
		printf("%s", "Error opening file\n");
		return -1;
	}
	int maxN = 20;
	float *data = malloc(maxN * sizeof(float));
	load_data(data, maxN);
	close_file();
	return 0;
}

/*
 * Print Results:
 *
 * Called after data is loaded and sorted.
 *
 * Prints the statistical results, neatly formatted and
 * colored in the terminal with ANSI escape codes.
 *
 * Calls to compute_mean, compute_median and compute_stddev
 * are embedded in the final arguments of printf calls.
 *
 * Besides the mean, median and standard deviation, the
 * number of elements and number of empty array entries
 * are also displayed.
 *
 * data - pointer to the array of float values in memory
 * n - the total number of elements in the array
 * maxN - the maximum number of floats the array can store
 */
void print_results(float *data, int n, int maxN) {
	int unused = maxN - n;
	float unusedPct = (float) unused / (float) maxN * 100.0;
	printf(ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET":\n%s\n", "Results", "--------");
	printf(ANSI_COLOR_GREEN"%4s"ANSI_COLOR_RESET"%7s"ANSI_COLOR_RED"%14d\n"ANSI_COLOR_RESET, "Num ", "values:", n);
	printf("%11s"ANSI_COLOR_RED"%14.3f\n"ANSI_COLOR_RESET, "mean:", compute_mean(data, n));
	printf("%11s"ANSI_COLOR_RED"%14.3f\n"ANSI_COLOR_RESET, "median:", compute_median(data, n));
	printf("%11s"ANSI_COLOR_RED"%14.3f\n"ANSI_COLOR_RESET, "stddev:", compute_stddev(data, n));
	printf(ANSI_COLOR_GREEN"%6s"ANSI_COLOR_RESET"%10s"ANSI_COLOR_RED"%d %s%.1f%s\n"ANSI_COLOR_RESET, "Unused"," capacity: ", unused, "(", unusedPct, "%)");
}

/*
 * Load Data:
 *
 * Called by main function.
 *
 * Loads float values from the input file into an
 * array in memory, with space for 20 floats to start.
 *
 * Keeps track of the number of entries in the array,
 * and calls enlarge_array when more space is needed.
 *
 * After loading all data, sorts the data and then
 * calls print_results to complete the program.
 *
 * data - pointer to the array of float values in memory
 * maxN - the maximum number of floats the array can store
 */
void load_data(float *data, int maxN) {
	int ret;
	int n = 0;
	while ((ret = read_float(&data[n])) != -1)
	{
		n++;
		if (n == maxN) {
			data = enlarge_array(data, n);
			maxN = 2 * maxN;
		}
	}
	qsort(data, n, sizeof(float), float_comparator);
	print_results(data, n, maxN);
}

/*
 * Enlarge Array:
 *
 * Called by load_data whenever the array of float
 * values reaches its maximum capacity.
 *
 * Allocates space for a new array with twice the
 * capacity, then copies over the values from the
 * old array before freeing the space in memory.
 *
 * data - pointer to the array of float values in memory
 * n - the total number of elements in the array
 * returns a pointer to the new array of floats
 */
float* enlarge_array(float *data, int n) {
	int maxN = 2 * n;
	float *new =  malloc(maxN * sizeof(float));
	int i;
	for (i = 0; i < n; i++) {
		new[i] = data[i];
	}
	free(data);
	return new;
}

/*
 * Float Comparator:
 *
 * Used by qsort to compare float values while sorting.
 *
 * Returns 1 if f1 > f2, 0 if f1 == f2, -1 otherwise
 */
int float_comparator(const void *v1, const void *v2) {
	float f1 = *(const float*) v1;
	float f2 = *(const float*) v2;
	return (f1 > f2) - (f1 < f2);
}

/*
 * Compute Mean:
 *
 * Sums up an array of float values and divides by
 * the total number of values to compute the average.
 *
 * data - pointer to the array of float values in memory
 * n - the total number of elements in the array
 * returns the arithmetic mean (average) float value
 */
float compute_mean(float *data, int n) {
	float sum = 0;
	int i;
	for (i = 0; i < n; i++) {
		sum += data[i];
	}
	return sum/n;
}

/*
 * Compute Median:
 *
 * Finds the middle value in a sorted array of floats.
 *
 * Uses modulo to determine if number of values is
 * even or odd. If n is odd, returns the middle element.
 * If n is even, returns the average of the two values
 * to the left and right of center.
 *
 * data - pointer to the SORTED array of float values
 * n - the total number of elements in the array
 * returns the median float value
 */
float compute_median(float *data, int n) {
	int mod;
	int i = n/2;
	if ((mod = n % 2) == 1) {
		return data[i];
	} else {
		return (data[i] + data[i-1])/2;
	}

}

/*
 * Compute Standard Deviation:
 *
 * Computes the population standard deviation for the
 * values stored in an array of floats, according to
 * the function:
 *
 * stddev = sqrt((sum((xi - mean)^2))/N)
 *
 * where the sum() goes from 1 to N, xi is the i-th element,
 * N is the number of elements in the data set, and sqrt()
 * is the square root function.
 *
 * data - pointer to the SORTED array of float values
 * n - the total number of elements in the array
 * returns the standard deviation float value
 */
float compute_stddev(float *data, int n) {
	float mean = compute_mean(data, n);
	float s = 0;
	int i;
	for (i = 0; i < n; i++) {
		s += pow(data[i] - mean, 2);
	}
	return sqrt(s/n);
}
