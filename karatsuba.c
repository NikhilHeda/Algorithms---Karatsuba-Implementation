#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

void append_zero(char* a, char *b);
double timediff(struct timespec start, struct timespec end);

int main() {
	
//	struct timespec start, end;
	char* a;
	char* b;
	a = (char *) malloc(sizeof(char) * 1000);
	b = (char *) malloc(sizeof(char) * 1000);
	scanf("%s", a);
	scanf("%s", b);
//	clock_gettime(CLOCK_REALTIME, &start);

	append_zero(a, b);

	printf("%s\n", a);
	printf("%s\n", b);

//	clock_gettime(CLOCK_REALTIME, &end);
//	printf("Execution time: %.6lf millisec.\n", timediff(start,end));
	return 0;
}

void append_zero(char* a, char *b) {
	int l1 = strlen(a);
	int l2 = strlen(b);
	int max = (l1 < l2) ? l2 : l1;
	int n1, n2;
	int i = 1;
	int k = 0;
	while(i < max)
	{
		i = i * 2;
		k++;
	}

	char* str1;
	char* str2; 
	str1 = (char *) malloc(sizeof(char) * 1000);
	str2 = (char *) malloc(sizeof(char) * 1000);

	n1 = i - l1;	//no.of zero's to append in 1st string
	n2 = i - l2;	//no.of zero's to append in 2nd string

	for(i = 0; i < n1; i++)
	{
		strcat(str1, "0");
	}

	for(i = 0; i < n2; i++)
	{
		str2[i] = '0';
	}

	strcat(str1, a);
	strcat(str2, b);

	strcpy(a, str1);	//destination, source
	strcpy(b, str2);

//	printf("%s\n", str1);
//	printf("%s\n", str2);
}

double timediff(struct timespec start, struct timespec end) {
	double t = (end.tv_sec - start.tv_sec)*1000;
	t += (end.tv_nsec - start.tv_nsec)*0.000001;
	return t;
}
