#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int char_to_int(char c);
char int_to_char(int n);
char* karatsuba(char* a, char* b, int k);
int calculate_k(int num);
void append_zero(char* a, char* b);
double timediff(struct timespec start, struct timespec end);

int main() {
	
//	struct timespec start, end;
	char* a;
	char* b;
	a = (char*) malloc(sizeof(char) * 1000);
	b = (char*) malloc(sizeof(char) * 1000);
	scanf("%s", a);
	scanf("%s", b);
//	clock_gettime(CLOCK_REALTIME, &start);

	append_zero(a, b);
	int k = calculate_k(strlen(a));

	printf("%s\n", karatsuba(a, b, k));

//	printf("%s\n", a);
	printf("%s\n", b);

//	clock_gettime(CLOCK_REALTIME, &end);
//	printf("Execution time: %.6lf millisec.\n", timediff(start,end));
	return 0;
}

char* karatsuba(char* a, char* b, int k) {
	if(k == 0) {
		int temp = char_to_int(a[0]) * char_to_int(b[0]);
		char* result;
		result = (char*) malloc(sizeof(char) * 2);
/*		int i = 0;
		while (temp > 0) {
			result[i] = int_to_char(temp % 10);
			temp = temp / 10;
			i++;
		}
		strrev(result);	//strrev not working. Don't know why
*/
		result[0] = int_to_char(temp / 10);
		result[1] = int_to_char(temp % 10);
		return result;
	}
	int m = (int) pow(2, k);
	char* a1;
	char* a2;
	char* b1;
	char* b2;

	a1 = (char*) malloc(sizeof(char) * 1000);
	a2 = (char*) malloc(sizeof(char) * 1000);
	b1 = (char*) malloc(sizeof(char) * 1000);
	b2 = (char*) malloc(sizeof(char) * 1000);

	a1 = a;
	a2 = &a[m/2];
	b1 = b;
	b2 = &b[m/2];

}

int char_to_int(char c) {
	return c - '0';
}

char int_to_char(int n) {
	return (char)(n + '0');
}


void append_zero(char* a, char *b) {
	int l1 = strlen(a);
	int l2 = strlen(b);
	int max = (l1 < l2) ? l2 : l1;
	int n1, n2;
	int i = (int) pow(2, calculate_k(max));
	char* str1;
	char* str2;

	str1 = (char *) malloc(sizeof(char) * 1000);
	str2 = (char *) malloc(sizeof(char) * 1000);

	n1 = i - l1;	//no.of zero's to append in 1st string
	n2 = i - l2;	//no.of zero's to append in 2nd string

	for(i = 0; i < n1; i++) {
		strcat(str1, "0");
	}

	for(i = 0; i < n2; i++) {
		str2[i] = '0';
	}

	strcat(str1, a);
	strcat(str2, b);

	strcpy(a, str1);	//destination, source
	strcpy(b, str2);

//	printf("%s\n", str1);
//	printf("%s\n", str2);
}

int calculate_k(int num) {
	int i = 1;
	int k = 0;
	while(i < num) {
		i = i * 2;
		k++;
	}
//	printf("%d\n", k);
	return k;
}

double timediff(struct timespec start, struct timespec end) {
	double t = (end.tv_sec - start.tv_sec)*1000;
	t += (end.tv_nsec - start.tv_nsec)*0.000001;
	return t;
}
