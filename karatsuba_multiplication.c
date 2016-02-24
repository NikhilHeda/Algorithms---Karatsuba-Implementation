#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int get_decimal(char d){
	return d - '0';
}
dfcdf;

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

/*
char *karatsuba(char *A, char *B, int k){
	//Multiplication of large integers a and b of 2 k decimal digits
	if (k = 0){
			return a*b;
	}
	
	int n = (int)pow(2, k);
	
	char *A1 = &A[0];
	char *A2 = &A[n/2];
	char *B1 = &B[0];
	char *B2 = &B[n/2];
	
	char *p1 = karatsuba(A1, B1, k-1)
	char *p2 = karatsuba(A2, B2, k-1)
	char *p3 = karatsuba(add(A1, A2), add(B1, B2), n/2);
	
	return add(add( add_zeroes(p1, n), add_zeroes((p3-p2-p1), n/2) ), p2); 

}
*/

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