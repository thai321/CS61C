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
    char temp = *x;
    *x = *y;
    *y = temp;
}

/* Flips the elements of a square array ARR across the y-axis. */
void flip_horizontal(unsigned char *arr, int width) {
    /* Optional function */
    int x, y;
	for (y = 0; y < width*width; y += width) {
	    for (x = 0; x < width/2; x += 1) {
	      swap(arr + y + x, arr + width + y - x -1); // Changed from &arr[___] syntax to arr + ___
	    }
	}

}

/* Transposes the square array ARR. */
void transpose(unsigned char *arr, int width) {
    /* Optional function */
    	unsigned char arr2[width*width];

    int x, y, i = 0;
    for(x = 0; x < width; x++) {
    	for(y = 0; y < width*width; y += width) {
    		*(arr2 + (i++)) = *(arr + x + y);
    	}
    }
    for(i = 0; i < width*width; i++) {
      arr[i] = arr2[i];
    }
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
    /* YOUR CODE HERE */
    int i;
    unsigned char copy[t_width*t_width];
    for(i = 0; i < t_width*t_width; i++) {
      copy[i] = template[i];
    }
    
    int y, x;
    for(y = 0; y<= (i_height - t_width)*i_width ; y += i_width) {
    	for(x = 0; x <= (i_width - t_width) ; x++) {
    		int temp = get_min_dist(image + x + y, template, t_width, i_width);
    		if(temp < min_dist)
    			min_dist = temp;
    	}
    }	



    return min_dist;

}   

int get_min_dist(unsigned char *image, 
        unsigned char *template, int t_width, int i_width) {

	int i;
    unsigned char copy[t_width*t_width];
    for(i = 0; i < t_width*t_width; i++) {
      copy[i] = template[i];
    }


    int y,x;
    i = 0;
    unsigned char im[t_width*t_width];
    for(y = 0; y < t_width*i_width; y += i_width) {
    	for( x = 0; x < t_width; x++) {
    		im[i++] = image[y + x];
    	}
    }
   printf("get bug y*x = %d ", x*y);
    unsigned int min_dist = squared_Euclidean(im, copy , t_width);

    flip_horizontal(copy, t_width);
    int temp = squared_Euclidean(im, copy, t_width);
    if(temp < min_dist)
    	min_dist = temp;


    for(i = 0; i < 3; i++) {
    	transpose(copy,t_width);
    	int temp2 = squared_Euclidean(im, copy, t_width);
    	if(temp2 < min_dist)
    		min_dist = temp2;

    	flip_horizontal(copy, t_width);
    	temp2 = squared_Euclidean(im, copy, t_width);
    	if(temp2 < min_dist)
    		min_dist = temp2;
    }


	return min_dist;
}
int squared_Euclidean(unsigned char *im, unsigned char *tem, int dim) {
	int i, result = 0;
	for(i = 0; i < dim*dim; i++) {
   		result += (int) (im[i] - tem[i])* (*(im + i) - *(tem + i));
   	}
   	return result;
}






    // int x1 = squared_Euclidean(image, copy , t_width);

    
    // flip_horizontal(copy, t_width);
    // int x1f = squared_Euclidean(image, copy , t_width);
  

    // transpose(copy,t_width);
    // int x2 = squared_Euclidean(image, copy , t_width);
   


    // flip_horizontal(copy,t_width);
    // int x2f = squared_Euclidean(image, copy , t_width);
    

    // transpose(copy,t_width);
    // int x3 = squared_Euclidean(image, copy , t_width);
    
    

    // flip_horizontal(copy,t_width);
    // int x3f = squared_Euclidean(image, copy , t_width);
 


    // transpose(copy,t_width);
    // int x4 = squared_Euclidean(image, copy , t_width);


    // flip_horizontal(copy,t_width);
    // int x4f = squared_Euclidean(image, copy , t_width);


    // transpose(copy,t_width);
    

    // x1 = squared_Euclidean(image, copy, t_width);


