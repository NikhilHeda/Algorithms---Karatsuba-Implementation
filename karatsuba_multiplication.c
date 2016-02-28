#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int get_decimal(char d){
	return d - '0';
}

char get_character(int d){
	return (char) (d + '0');
}

int get_first_digit(int n){
	int d = (int)log10(n);
	return n / pow(10, d);
}

int get_last_digit(int n){
	return n % 10;
}

int get_nearest_power(int a){
	int i;
	int k = 0;
	for (i = 1; i < a; i *= 2)
		k++;
	return k;
}

char *prepend_zeroes(char *A, int n){
	char *res = (char *) malloc(sizeof(char) * (n + 1));
	int i;
	for (i = 0; i < n; i++)
		res[i] = '0';
	res[i] = '\0';
	return strcat(res, A);
}

char *append_zeroes(char *A, int n){
	char *res = (char *) malloc(sizeof(char) * (n + 1));
	int i;
	for (i = 0; i < n; i++)
		res[i] = '0';
	res[i] = '\0';
	return strcat(A, res);
}

char *add(char *A, char *B){
	int a = strlen(A);
	int b = strlen(B);
	
	int size = (a > b ? a : b);
	
	int temp_sum, carry = 0, i, j, k;
	
	char *sum = (char *) malloc(sizeof(char) * (size + 2) );
	
	for (i = a - 1, j = b - 1, k = size; i > -1 && j > -1; i--, j--, k--){
		temp_sum = carry + get_decimal(A[i]) + get_decimal(B[j]) ;
		if (temp_sum > 9)
			carry = get_first_digit(temp_sum);
		else
			carry = 0;
		sum[k] = get_character(get_last_digit(temp_sum));
	}
	
	if(i != -1){
		while(i > -1){
			temp_sum = carry + get_decimal(A[i--]);		
			if (temp_sum > 9)
				carry = get_first_digit(temp_sum);
			else
				carry = 0;
			sum[k--] = get_character(get_last_digit(temp_sum));
		}
	}else{
		while(j > -1){
			temp_sum = carry + get_decimal(B[j--]);
			if (temp_sum > 9)
				carry = get_first_digit(temp_sum);
			else
				carry = 0;
			sum[k--] = get_character(get_last_digit(temp_sum));
		}
	}
	
	sum[k] = get_character(carry);
	sum[size+1] = '\0';
	return sum;
}

// Always A is greater than B
char *sub(char *A, char *B){
	int a = strlen(A);
	int b = strlen(B);
	
	int size = (a > b ? a : b);
	
	int temp_diff, i, j, k, p;
	
	char *diff = (char *) malloc(sizeof(char) * (size + 1) );

	for (i = a - 1, j = b - 1, k = size - 1; i > -1 && j > -1; i--, j--, k--){
		int n1 = get_decimal(A[i]);
		int n2 = get_decimal(B[j]);
		if (n1 >= n2)
			temp_diff = n1 - n2;
		else{
			for (p = i - 1; A[p] == '0' && p > -1; p--)
				;
			for (int q = p; q < i; q++){
				if (A[q] == '0')
					A[q] = '9';
				else
					A[q] = get_character(get_decimal(A[q]) - 1);
			}
			temp_diff = (10 + get_decimal(A[i])) - get_decimal(B[j]);
		}
		diff[k] = get_character(temp_diff);
	}
	diff[size] = '\0';

	if(i != -1){
		while(i > -1)
			diff[k--] = A[i--];
	}

	return diff;
}

char *karatsuba(char *A, char *B, int k){
	//Multiplication of large integers a and b of 2 k decimal digits
	if(k == 0) {
		int temp = get_decimal(A[0]) * get_decimal(B[0]);
		char* result;
		result = (char*) malloc(sizeof(char) * 2);
		result[0] = get_character(temp / 10);
		result[1] = get_character(temp % 10);
		return result;
	}
	
	int n = (int)pow(2, k);
	
	char *A1 = &A[0];
	char *A2 = &A[n/2];
	char *B1 = &B[0];
	char *B2 = &B[n/2];

	char *p1 = karatsuba(A1, B1, k-1);
	printf("p1: %s\n", p1);

	char *p2 = karatsuba(A2, B2, k-1);
	printf("p2: %s\n", p2);

	char *p3 = karatsuba(add(A1, A2), add(B1, B2), k);
	printf("p3: %s\n", p3);

/*
	char *temp1 = append_zeroes(p1, n);

	char *temp2 = sub(sub(p3, p2), p1);

	temp2 = append_zeroes(temp2, n/2);

	return add(add(temp1, temp2), p2);
*/
}

int main(){
	char *A;
	char *B;
	A = (char *) malloc(sizeof(char) * 1000);
	B = (char *) malloc(sizeof(char) * 1000);
	
	scanf(" %[^\n]", A);
	scanf(" %[^\n]", B);
	
	int a = strlen(A);
	int b = strlen(B);

	int k = get_nearest_power(a > b ? a : b);
	A = prepend_zeroes(A, ((int)pow(2, k)) - a);
	B = prepend_zeroes(B, ((int)pow(2, k)) - b);
	printf("%s\n", karatsuba(A, B, k));

	/*
	
	char *sum = add(A, B);
	printf("%s\n", sum);

	char *diff = sub(A, B);
	printf("%s\n", diff);
	*/

	return 0;
}