#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



long long int get_decimal(char d){
	return d - '0';
}

char get_character(long long int d){
	return (char) (d + '0');
}

long long int get_first_digit(long long int n){
	long long int d = (long long int)log10(n);
	return n / pow(10, d);
}

long long int get_last_digit(long long int n){
	return n % 10;
}

long long int get_nearest_power(long long int a){
	long long int i;
	long long int k = 0;
	for (i = 1; i < a; i *= 2)
		k++;
	return k;
}

char *prepend_zeroes(char *A, long long int n){
	printf("A: %s\n", A);
	char *res = (char *) malloc(sizeof(char) * (n + 1));
	long long int i;
	for (i = 0; i < n; i++)
		res[i] = '0';
	res[i] = '\0';
	printf("res: %s\n", res);
	return strcat(res, A); // Probably here we are getting a segmentation fault.
}

char *append_zeroes(char *A, long long int n){
	char *res = (char *) malloc(sizeof(char) * (n + 1));
	long long int i;
	for (i = 0; i < n; i++)
		res[i] = '0';
	res[i] = '\0';
	return strcat(A, res);
}

char *add(char *A, char *B){
	long long int a = strlen(A);
	long long int b = strlen(B);
	
	long long int size = (a > b ? a : b);
	
	long long int temp_sum, carry = 0, i, j, k;
	
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
	long long int s = strlen(sum);
	long long int m=0;

	for(m=0;m<s&&sum[m]=='0';m++);
	return &sum[m];
	
	
}

// Always A is greater than B
char *sub(char *A, char *B){
	long long int a = strlen(A);
	long long int b = strlen(B);
	
	long long int size = (a > b ? a : b);
	
	long long int temp_diff, i, j, k, p;
	
	char *diff = (char *) malloc(sizeof(char) * (size + 1) );

	for (i = a - 1, j = b - 1, k = size - 1; i > -1 && j > -1; i--, j--, k--){
		long long int n1 = get_decimal(A[i]);
		long long int n2 = get_decimal(B[j]);
		if (n1 >= n2)
			temp_diff = n1 - n2;
		else{
			for (p = i - 1; A[p] == '0' && p > -1; p--)
				;
			for (long long int q = p; q < i; q++){
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

char *karatsuba(char *A, char *B, long long int k){
	//Multiplication of large long long integers a and b of 2 k decimal digits
	/*
	printf("\nA:%s\tB:%s\tk:%lld",A,B,k);
	if(k == 2 && strlen(A) == 4 && strlen(B) == 4 && A[0] == '0' && B[0] == '0'&& A[1] == '0' && B[1] == '0'&& A[2] == '0' && B[2] == '0') {
		long long int temp = get_decimal(A[3]) * get_decimal(B[3]);
		char* result;
		result = (char*) malloc(sizeof(char) * 3);
		result[0] = get_character(temp / 10);
		result[1] = get_character(temp % 10);
		result[2]='\0';
		printf("base case k=1 returns :%s\n",result);
		return result;
	}
	
	else if(k == 1 && strlen(A) == 2 && strlen(B) == 2 && A[0] == '0' && B[0] == '0') {
		long long int temp = get_decimal(A[1]) * get_decimal(B[1]);
		char* result;
		result = (char*) malloc(sizeof(char) * 3);
		result[0] = get_character(temp / 10);
		result[1] = get_character(temp % 10);
		result[2]='\0';
		printf("base case k=1 returns :%s\n",result);
		return result;
	}
	else 
	*/
	if(k == 0)
	{
		long long int temp = get_decimal(A[0]) * get_decimal(B[0]);
		char* result;
		result = (char*) malloc(sizeof(char) * 3);
		result[0] = get_character(temp / 10);
		result[1] = get_character(temp % 10);
		result[2]='\0';
		printf("base case k=0 returns :%s\n",result);
		return result;
	}
	
	long long int n = (long long int)pow(2, k);
	
	char *A1 = (char *)malloc((n/2+1)*sizeof(char));
	strncpy(A1,A,n/2);
	A1[n/2] = '\0';
	
	char *A2 = &A[n/2];
	
	char *B1 = (char *)malloc((n/2+1)*sizeof(char));
	strncpy(B1,B,n/2);
	B1[n/2]='\0';

	char *B2 = &B[n/2];
	printf("\nA1:%s\tA2:%s\tB1:%s\tB2:%s\t",A1,A2,B1,B2);
	
	printf("\n****p1****\n");
	long long int k_for_p1 = get_nearest_power(strlen(A1));
	char *p1 = karatsuba(A1, B1, k_for_p1);
	printf("\np1:%s",p1);

	printf("\n****p2****\n");
	long long int k_for_p2 = get_nearest_power(strlen(A2));
	char *p2 = karatsuba(A2, B2, k_for_p2);
	printf("\np2:%s",p2);
	
	/*long long int newk = get_nearest_power(strlen(add(A1,A2)));
	printf("\nnewk:%lld",newk);
	
	printf("\n****p3****\n");*/
	char* Asum=add(A1,A2);
	char*Bsum=add(B1,B2);
	long long int a = strlen(Asum);
	long long int b = strlen(Bsum);
	

	long long int newk = get_nearest_power(a > b ? a : b);
	Asum = prepend_zeroes(Asum, ((long long int)pow(2, newk)) - a);
	Bsum = prepend_zeroes(Bsum, ((long long int)pow(2, newk)) - b);
	printf("%s\n", karatsuba(A, B, k));
	char *p3 = karatsuba(Asum, Bsum, newk);
	printf("\np3:%s",p3);

	char *temp1 = sub(p3,p1);
	printf("\np3-p1:%s",temp1);
	char *temp2 = sub(temp1, p2);
	printf("\np3-p2-p1:%s",temp2);

	temp2 = append_zeroes(temp2, n/2);
	char *temp3 = append_zeroes(p1, n);
	printf("\ntemp2:%s,temp3:%s",temp2,temp3);
	
	printf("\nWhat are u returning? : %s\n",add(add(temp3, temp2), p2));

	return add(add(temp3, temp2), p2);
}

int main(){
	char *A;
	char *B;
	A = (char *) malloc(sizeof(char) * 100000000);
	B = (char *) malloc(sizeof(char) * 100000000);
	
	scanf(" %[^\n]", A);
	scanf(" %[^\n]", B);
	
	printf("A:%s,B:%s",A,B);
	
	long long int a = strlen(A);
	long long int b = strlen(B);

	long long int k = get_nearest_power(a > b ? a : b);
	A = prepend_zeroes(A, ((long long int)pow(2, k)) - a);
	B = prepend_zeroes(B, ((long long int)pow(2, k)) - b);
	
		printf("A:%s\nB:%s\n\n\n",A,B);

	printf("**calling karatsuba**");
	printf("%s\n", karatsuba(A, B, k));

	return 0;
}
