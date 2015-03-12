
#include "matcher.h"
#include <stdio.h>
/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int bracket(char *, char *, int);
int char_value(char);
int check;
int traceL = 0;
int traceP = 0;
int rgrep_matches(char *line, char *pattern) {
	// printf("Adress of line = %p, value of line  = %c\n", line, *line);
	// printf("Adress of pattern = %p, value of pattern = %c\n\n", pattern, *pattern);
	// if(*pattern == '\\'){
	// 	printf("Hello man\n");
	// }
	// printf("value = %c\n", *(pattern ));
	// printf("traceL = %d, traceP = %d\n\n", traceL, traceP);
	char next = *(pattern+1);
	if(*pattern == '\0'){
		printf("Done Pattern\n");
		traceL = traceP = 0; 
		return 1;
	}
	if(*line == '\0') {
		printf("Done line\n");
		traceL = traceP = 0; 
		return 0;
	}
	
	switch (*pattern) {
	case '.':

		// if(next == '{') {
		// 	if( (*(pattern + 2) == '0') &&  (*(pattern + 4) == '0') ) {
		// 		traceP++;
		// 		return bracket(line, pattern + 1, 0 );
		// 	}
		// 	return 0;
		// }
		if(next == '{') {
			if(*(pattern+2) == '0') {
				if(*(pattern + 4) == '}') {
					printf("Later\n");
					return 0;
				}
				else if(*(pattern + 4) == '0') {
					return bracket(line, pattern, 0);
				}
				else {
					printf("Later");
				}

			}
		}
		else {//if((next == '.' && *(line + 1)) ) {// || (*(pattern + 2) != '\\') || (*(pattern + 2) != '{' )) {	
			if(*(line + 1) == '\0') {
				traceL = traceP = 0; 
				return 0;
			}
				
			traceL++;
			traceP++;
			// printf("period\n");
			return rgrep_matches(line + 1, pattern + 1);	
		}
  		break;
 	 
	case '\\':
	
		if(next == '\0')    // case of line = 'babacdef' and pattern = 'babacde\'
			return 1;		// \ appear end of pattern

		// check next of next of pattern == { for bracket case
	//--->should be next of next
		else if(*(pattern + 2) == '{') {
			if(*(pattern + 3) == '0') {
			 	if(*(pattern + 5) == '0') {
			 		traceP++;
			 		return bracket(line, pattern + 1,0);
			 	}
			}
			
		}
		else if(*line == next){
			traceL++;
			traceP +=2;
			return rgrep_matches(line + 1, pattern + 2);
		}
		
		else {
			line = line-traceL + 1;
			pattern = pattern - traceP;
			traceL = traceP = 0;
			return rgrep_matches(line, pattern);
		}
	  	break;

	default:
		if(next == '{') {
			if(*(pattern+2) == '0') {
				if(*(pattern + 4) == '0') {
					return bracket(line, pattern, 0);
				}
			}
		}
		else if(*line == *pattern) {
			traceL++;
			traceP++;
			return rgrep_matches(line + 1, pattern + 1);
		}
		else {
			line = line-traceL + 1;
			pattern = pattern - traceP;
			traceL = traceP = 0;
			return rgrep_matches(line, pattern);
		}

	break;
	}
	printf("hello\n");
   	return 1;
}
int char_value(char c) {
	return c -'0';
}
int bracket(char *line, char *pattern, int kind) {
	
	if(kind == 0) {
		traceP +=6;
		return rgrep_matches(line ,pattern + 6);
	}
	// else if(kind == 1) { //period case .{0,m}
	// 	// int m = char_value(*(pattern + 4));
	// 	// char next = *(pattern + 6);
	// 	// int i;
	// 	// for(i = 0; i < m; )
	// 	printf("later");
	// }
	// // else if(kind == )

	return 0;
}






















// int bracket(char *line, char *pattern) {
// 		// printf("Adress of line = %p, value of line  = %c\n", line, *line);
// 		// printf("Adress of pattern = %p, value of pattern = %c\n\n", pattern+1, *(pattern + 3));
// 	int begin = char_value(*(pattern + 1));
// 	int end = char_value(*(pattern + 3));
// 	// char next = *(pattern + 4);
// 	// printf("begin = %d\n", begin);
// 	// printf("end = %d\n",end);
// 	char previous = *(pattern - 1);

// 	if(begin == 0 && end == 0){
// 		if(*(pattern + 5) == '\0') {
// 			printf("begin = end = 0, done\n");
// 			return 0;
// 		}
// 		// printf("This one\n");
// 		// printf("Adress of line = %p, value of line  = %c\n", line, *line);
// 		// printf("Adress of pattern = %p, value of pattern = %c\n\n", pattern+1, *(pattern + 5));
// 		return rgrep_matches(line, pattern + 5);
// 	}

// 	int i ;
// 	for(i = 0; i < begin; i++) {
// 		if(*(line + i) != previous)
// 			return rgrep_matches(line + i + 1, pattern - 1);
// 	}
// 	i = 0;
// 	while(begin <= (begin + end) && *(line +i) ) {
// 		// if(*)
// 		if(*(line + begin+ i) != previous)
// 			// if(*(line + begin+ i) == next)
// 				// return rgrep_matches()
// 			return rgrep_matches(line + begin + i, pattern + 5);
// 		i++;
// 		begin++;
// 	}
// 	printf("No way\n");
// 	// if(*(pattern + 5) == '\0')
// 	// 	return 0;
// 	return rgrep_matches(line, pattern + 5);;
// }




// case '.':
	// 	if((*(pattern + 1) == '.' && *(line + 1)) || (*(pattern + 2) != '\\') || (*(pattern + 2) != '{' )) {	
	// 		printf("Period\n");	
	// 		return rgrep_matches(line + 1, pattern + 1);	
	// 	}
	// 	if(*(pattern + 1) == '\\') {
	// 		return rgrep_matches(line + 1, pattern + 2);
	// 	}
	// 	else {
	// 		return rgrep_matches(line + 1, pattern);
	// 	}
 //  		break;






// default:
// 		// printf("Enter default\n");
// 		if(*pattern == *line){
		
// 		// printf("Adress of line = %p, value of line  = %c\n", line, *line);
// 		// printf("Adress of pattern = %p, value of pattern = %c\n\n", pattern+1, *(pattern + 1));
//   			// printf("Enter {\n");
//   			if(*(pattern + 1) == '{') {
//   				printf("Enter bracket\n\n");
//   				return bracket(line, pattern + 1);
//   			}
//   			// return rgrep_matches(line + 1, pattern);
//   		}

//   		if(*pattern != *line && *(pattern + 1) == '{') {
//   			printf("He\n");
//   			int i;
//   			for(i = 0; *(line + i); i++){
//   				if(*(line + i) ==  *pattern)
//   					return rgrep_matches(line + i, pattern);
//   			}
//   			if(*(pattern + 6) == '\0') {
// 				if(check == 1)
// 					return 1;
// 				return 0;
// 			}
  				
//   			return rgrep_matches(line , pattern + 6);
//   		}
//   		if(*pattern == *line) {
//   			check = 1;
//   			printf("Here\n");
//   			return rgrep_matches(line + 1,pattern + 1);
//   		}
//   		if(*pattern != *line) {
//   			return rgrep_matches(line + 1,pattern );
//   		}
//   		// if(*(pattern + 1)) { // (*pattern != *line && *(pattern + 1)) 
//   		// 	return rgrep_matches(line + 1, pattern);
//   		// }

// 	break;
// 	}

/* This is matching any substring of string with a line without '.' , '\', '{' */
// int i,j;
// 	for(i = 0; *(line + i); i++) {
// 		for(j = 0; *(pattern + j) ; j++) {
// 			// printf("(*(pattern + j)) = %c ---> *(line + i + j)) = %c\n", *(pattern + j), *(line + i + j));
// 			if((*(pattern + j)) != *(line + i + j)) {
// 				// printf("Break!!!!\n");
// 				break;
// 			}
// 		}
// 		if((*(pattern + j)) == '\0')
// 			return 1;
// 	}
//    	return 0;

