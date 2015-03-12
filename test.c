#include <stdio.h>
int * ptr() {
	int y;
	y = 3;
	return &y;
}
int main() {
	int *stackAddr, content;
	stackAddr = ptr();

	content = *stackAddr;
	printf("%d\n", content);
	return 0;
}