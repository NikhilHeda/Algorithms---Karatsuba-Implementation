#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	char *A;
	char *B;
	A = (char *) malloc(sizeof(char) * 1000);
	B = (char *) malloc(sizeof(char) * 1000);
	
	scanf(" %[^\n]", A);
	scanf(" %[^\n]", B);
	
	char *sum = add(A, B);
	printf("%s", sum);
	
	return 0;
}