#include "matcher.h"
#include <stdio.h>
/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */

int rgrep_matches(char *line, char *pattern) {
	// int a = 1 , b = 2; 
	


	
    // if(*(line) == *pattern) {
    // 	if(*(++line) == *(++pattern)) {
    // 		return 1;
    // 	}
    // }
    // return 0;
	// int a = 0;
    // while(*pattern) {
    // 	if(*(line++) != *(pattern++)) {
    // 		return 0;
    // 	}
    // 	printf("hello\n");
    // }
	int i, j;
    for(i = 0; *(line + i); i++) {
    	for(j = 0; *(pattern + j);j++) {
    		if(!(*(pattern + j + 1)))
    			return 1;
    		if(*(line + i) != *(pattern + j))
    			break;    		
    	}
    }
    return 0;

	// while(*pattern) {
	// 	if(*pattern == '.') {
	// 		if(!(*(++line)))
	// 			return 1;
	// 		if(*(++pattern) == '.') {
	// 			return rgrep_matches(++line, pattern);
	// 		}
	// 	}
	// 	else {
	// 		if(*line != *pattern)
	// 			return 0;
	// 		return rgrep_matches(++line, ++pattern); 
	// 	}
	// }


     // return 1;
}
