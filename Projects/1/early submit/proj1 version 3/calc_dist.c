/*
 * PROJ1-1: YOUR TASK A CODE HERE
 *
 * You MUST implement the calc_min_dist() function in this file.
 *
 * You do not need to implement/use the swap(), flip_horizontal(), transpose(), or rotate_ccw_90()
 * functions, but you may find them useful. Feel free to define additional helper functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include "digit_rec.h"
#include "utils.h"
#include "limits.h"

int get_min_dist(unsigned char *image,
        unsigned char *template, int t_width, int i_width);

int squared_Euclidean(unsigned char *, unsigned char *, int);
/* Swaps the values pointed to by the pointers X and Y. */
void swap(unsigned char *x, unsigned char *y) {
    /* Optional function */
}

/* Flips the elements of a square array ARR across the y-axis. */
void flip_horizontal(unsigned char *arr, int width) {
    /* Optional function */
}

/* Transposes the square array ARR. */
void transpose(unsigned char *arr, int width) {
    /* Optional function */
}

/* Rotates the square array ARR by 90 degrees counterclockwise. */
void rotate_ccw_90(unsigned char *arr, int width) {
    /* Optional function */
}

/* Returns the squared Euclidean distance between TEMPLATE and IMAGE. The size of IMAGE
 * is I_WIDTH * I_HEIGHT, while TEMPLATE is square with side length T_WIDTH. The template
 * image should be flipped, rotated, and translated across IMAGE.
 */
unsigned int calc_min_dist(unsigned char *image, int i_width, int i_height, 
        unsigned char *template, int t_width) {
    unsigned int min_dist = UINT_MAX;  

    min_dist = squared_Euclidean(image,template , t_width);

    return min_dist;
}   

int squared_Euclidean(unsigned char *im, unsigned char *tem, int dim) {
    int i, result = 0;
    for(i = 0; i < dim*dim; i++) {
        result += (int) (im[i] - tem[i])* (*(im + i) - *(tem + i));
    }
    return result;
}


