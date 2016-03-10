#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
void reverse(char *);
void subtract(char*,char*,char*);
int compare(char *,char *);
void removeZero(char *);
void add(char*,char*,char*);
void split_at(char*,int,char*,char*);
void cal(char*,char*,char*,char*,int,int);
char* karatsuba(char*,char*);
int manipulate(char*,char*);
int main() {
    char *num1;
    char *num2;
    num1 = malloc(1048600);
    num2 = malloc(1048600);
    scanf("%s%s",num1,num2);
    char *answer;
    answer=karatsuba(num1,num2);
    removeZero(answer);
    printf("%s\n",answer);
    return 0;
}
char* karatsuba(char *a,char *b) {
    int k=manipulate(a,b);
    if (k == 1) {
        int k,l;
        k=a[0]-'0';
        l=b[0]-'0';
        k*=l;
        char *newres;
        newres=malloc(3);
        if(k>9){
            l=k%10;
            k/=10;
            newres[0]=k+'0';
            newres[1]=l+'0';
            newres[2]='\0';
        }
        else {
            newres[0]=k+'0';
            newres[1]='\0';
        }
        return newres;
    }
    int i;
    long mem = 2*k;
    int m2 = k/2;
    char *a1,*a2,*b1,*b2,*result,*temp1,*temp2;
    a1=malloc(m2+2);
    a2=malloc(m2+2);
    b1=malloc(m2+2);
    b2=malloc(m2+2);
    temp1=malloc(mem+3);
    temp2=malloc(mem+3);
    result=malloc(mem+3);
    split_at(a, m2,a1,a2);
    split_at(b, m2,b1,b2);
    char *p1 = karatsuba(a1, b1);
    removeZero(p1);
    char *p2 = karatsuba(a2, b2);
    removeZero(p2);
    add(a1,a2,temp1);
    add(b1,b2,temp2);
    char *p3 = karatsuba(temp1, temp2);
    removeZero(p3);
    cal(p1,p2,p3,result,k,m2);
    free(p1);
    free(p2);
    free(p3);
    free(a1);
    free(a2);
    free(b1);
    free(b2);
    free(temp1);
    free(temp2);
    return result;
}
int manipulate(char *num1,char *num2) {
	int k=1,size,j=0,i;
	if(strlen(num1)>=strlen(num2))                         //finding the max size of a and b.
		size=strlen(num1);
	else 
		size=strlen(num2);
    while(k<size)								//finds least k=2^m greater than max{strlen(a) and strlen(b)}
    {
    	k=k*2;
    	j++;
    }
    if(k==1)
    {
    	return 1;
    }
    int size1=strlen(num1);
    int size2=strlen(num2);
    reverse(num1);
    reverse(num2);
    for(i=0;i<k-size1;i++)                          //putting 'k-size' zeroes at the first of a and b array  
    {
    	num1[i+size1]='0';
    }
    num1[i+size1]='\0';
    for(i=0;i<k-size2;i++)
    {
    	num2[i+size2]='0';
    }
    num2[i+size2]='\0';
    reverse(num1);
    reverse(num2);
    return i+size2;
}
void cal(char *p1,char *p2,char *p3,char *result,int m,int m2) {
    //(p1*10^m)+((p3-p1-p2)*10^m2)+(p2)
    char *temp1,*temp2,*temp3;
    int len=strlen(p1),i,j;
    temp1=malloc(2*m+2); //(p1*10^m)
    temp2=malloc(2*m+2); //(p3-p1-p2)*10^m2
    temp3=malloc(2*m+2); //(p1*10^m)+((p3-p1-p2)*10^m2)
    i=0; j=0;
    while((temp1[i]=p1[i])!='\0')
        i++;
    while(j++<m)
        temp1[i++]='0';
    temp1[i]='\0';
    add(p1,p2,temp2);
    subtract(p3,temp2,temp3);
    i=0;
    while(temp3[i++]!='\0') ;
    --i;
    j=0;
    while((j++)<m2) 
        temp3[i++]='0';
    temp3[i]='\0';
    add(temp1,temp3,temp2);
    add(temp2,p2,temp1);
    i=0;
    while((result[i]=temp1[i])!='\0')
        i++;        
    free(temp1);
    free(temp2);
    free(temp3);
}
void split_at(char *a,int m,char *a1,char *a2) {
    int i;
    for(i=0;i<m;i++)
        a1[i]=a[i];
    a1[m]='\0';
    for(i=0;i<m;i++)
        a2[i]=a[m+i];
    a2[m]='\0';
}
void add(char *num1,char *num2,char *result) {
    char *ref;
    int i=0,carry=0;
    reverse(num1);
    reverse(num2);
    while(num1[i]!='\0'&&num2[i]!='\0') {
        result[i]=num1[i]+num2[i]-'0'+carry;
        carry=0;
        if(result[i]>57) {
            result[i]-=10;
            carry=1;
        }
        i++;
    }
    if(num1[i]!='\0') 
        ref=num1;
    else
        ref=num2;
    while(ref[i]!='\0') {
        result[i]=ref[i]+carry;
        carry=0;
        if(result[i]>57) {
            result[i]-=10;
            carry=1;
        }
        i++;
    }
    if(carry==1) {
        result[i++]='1';
    }
    result[i]='\0';
    reverse(num1);
    reverse(num2);
    reverse(result);
}
void subtract(char *num1,char *num2,char *result) {
    char *ref,flag=0;
    int i=0,borrow=0;
    reverse(num1);
    reverse(num2);
    if(compare(num1,num2)==-1){
        printf("wrong");
        flag=1;
        ref=num1;
        num1=num2;
        num2=ref;
    }
    while(num1[i]!='\0'&&num2[i]!='\0') {
        result[i]=num1[i]-num2[i]+'0'-borrow;
        borrow=0;
        if(result[i]<48) {
            result[i]+=10;
            borrow=1;
        }
        i++;
    }
    while(num1[i]!='\0') {
        result[i]=num1[i]-borrow;
        borrow=0;
        if(result[i]<48) {
            result[i]+=10;
            borrow=1;
        }
        i++;
    }
    if(flag==1) {
        result[i++]='-';
        ref=num1;
        num1=num2;
        num2=ref;
    }
    result[i]='\0';
    reverse(num1);
    reverse(num2);
    reverse(result);
    removeZero(result);
}
void reverse(char *str) {
    int i=0,j=0;
    char c;
    while(str[j++]!='\0') ;
    j-=2;
    while(i<j) {
       c=str[i];
       str[i++]=str[j];
       str[j--]=c;
    }
}
int compare(char *num1,char *num2) {
    int i=0,cmp=0;
    while(num1[i]!='\0'&&num2[i]!='\0') {
        if(num1[i]>num2[i])
            cmp=1;
        else if(num1[i]<num2[i])
            cmp=-1;
        i++;
    }
    if(num1[i]!='\0'&&num2[i]=='\0') return 1;
    if(num2[i]!='\0'&&num1[i]=='\0') return -1;
    return cmp;
}
void removeZero(char *str) {
    int i=0,j=0;
    if(str[0]=='-'){
        i=j=1;
    }
    while(str[i]=='0') {i++;}
    if(i!=0) {
        while(str[i]!='\0')
            str[j++]=str[i++];
        str[j]='\0';
    }
    if(str[0]=='\0') {
        str[0]='0';
        str[1]='\0';
    }
}
