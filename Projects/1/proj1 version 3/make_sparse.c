/*
 * PROJ1-1: YOUR TASK B CODE HERE
 * 
 * Feel free to define additional helper functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include "sparsify.h"
#include "utils.h"


void free_elems(Row *row);
/* Returns a NULL-terminated list of Row structs, each containing a NULL-terminated list of Elem structs.
 * See sparsify.h for descriptions of the Row/Elem structs.
 * Each Elem corresponds to an entry in dense_matrix whose value is not 255 (white).
 * This function can return NULL if the dense_matrix is entirely white.
 */
Row *dense_to_sparse(unsigned char *dense_matrix, int width, int height) {
    /* YOUR CODE HERE */
    int i = 0;
    int x,y;
    int count = 0, count_Row = 0, count_element = 0;
    int white = 1;
    Elem *track = NULL;
    Row *head = NULL;
    Row *tail = NULL;

    for(y = 0; y < height*width; y += width) {
    	white = 1;
    	Row *row = (Row *) malloc(sizeof(Row));
    	row->y = y;
    	row->next = NULL;
    	row->elems->next = NULL;

    	for(x = 0; x < width; x++) {
    		if((int) dense_matrix[x + y] != 255) {
    			white = 0;

    			Elem *temp = (Elem *) malloc(sizeof(Elem));
    			temp->value = (int) dense_matrix[x+y];
    			temp->x = x;
    			temp->next = NULL;
    			
    			count_element++;
    			if(track == NULL) {
    				track = temp;
    			}
    			else {
    				track->next = temp;
    				track = temp;
    			}
    			if(count_element == 1) {
    				row->elems = track;
    			}
    		}
    	}
    	if(white) {
    		free(row);
    	}
    	else if(count_Row == 0 && row->elems != NULL) {
    		head = tail = row;
    		head->elems = NULL;
    		count_Row++;
    	}
    	else if(row->elems != NULL) {
    		tail->next = row;
    		tail = row;
    	}
    }

    return head;
}

/* Frees all memory associated with SPARSE. SPARSE may be NULL. */
void free_sparse(Row *sparse) {
    Row *node = sparse;
    Row *temp;
    while (node != NULL) {
	free_elems(node);
	temp = node;
	node = node -> next;
	free(temp);
    }	
}

void free_elems(Row *row) {
    Elem *node = row -> elems;
    Elem *temp = node;
    while (node != NULL) {
	temp = node;
	node = node -> next;
	free(temp);
    }	
}

