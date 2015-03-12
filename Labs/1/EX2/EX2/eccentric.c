#include <stdio.h>

int main(void) {
	int i=3, j=3, k=1, m=3;
	int a;
	char *s;
    
	printf("Berkeley eccentrics:\n====================\n");
    
	/* for loop */
	for(a=0; a<i; a++) {
		printf("Happy ");
	}
	printf("\n");
	
	/* switch statement */
	switch(j) {
		case 0:		printf("Yoshua\n");
		case 1: 	printf("Triangle Man\n");	break;
		case 2: 	printf("Chinese Erhu Guy\n");
		case 3: 	printf("Yoshua\n");		break;
		case 4:		printf("Dr. Jokemon\n");	break;
		case 5:		printf("Hat Lady\n");
		default:	printf("I don't know these people!\n");
	}
	
	/* ternary operator */
	s = (m==3) ? "Go" : "Boo";
    
	/* if statement */
	if(k) {
		printf("\n%s BEARS!\n",s);
	} else  {
		printf("\n%s CARDINAL!\n",s);
	}
    
	return 0;
}