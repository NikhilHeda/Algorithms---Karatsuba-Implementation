#include <stdio.h>
#include <stdlib.h>
#include<string.h>

char *inputString(FILE* fp, size_t size){

    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}//for accepting long input

long long int nearestpower(long long int x)
{
	long long int i=2;
	while(i<x)
	{
		i*=2;
	}
	return i;
}

char* generateString(long long int x)
{
	
    char *str;
    int ch;
    size_t len = 0;
    str = (char*)malloc(x*sizeof(char));//size is start size
    while(x!=0){
        str[len++]='0';
        
		x--;
        
    }
    str[len++]='\0';
	printf("%s %s","Zero string",str);

    return realloc(str, sizeof(char)*len);
}


char* conczero(char *x,long long int l)
{
	long long int final_Length=nearestpower(l);
	printf("%s\n","calculated fs");
	char *z=(char*)malloc((final_Length-l)*sizeof(char));
	printf("%s\n","allocated z");
	if(final_Length-l!=0)
	{
	z=generateString(final_Length-l);
	printf("Inside conc zero");
	
	}
	printf("%s\n","b4 allocated fs");
	char *fs=(char*)malloc(final_Length*sizeof(char));
	fs[0]='\0';
	printf("%s","allocated");
	if(final_Length-l!=0)
	{
	strcat(fs,z);
	free(z);
	printf("%s",fs);
	}
	strcat(fs,x);
	printf("%s",fs);
	printf("%s","final allocation");
	return realloc(fs, sizeof(char)*final_Length);
}


int main(void){
    char *a;
	char *b;
	long long int lena;
	long long int lenb;

    a = inputString(stdin, 100);
	b = inputString(stdin, 100);
	lena = (long long int)strlen(a);
	lenb = (long long int)strlen(b);
	
	a=conczero(a,lena);
	printf("\n%s","callingb");
	b=conczero(b,lenb);
	printf("\n%s","calledb");
	printf("%s","before printing");
    printf("%s\n", a);
	printf("%s\n", b);
	//printf("%s\n", fs);
	printf("%lld\n",(long long int) strlen(a));
	printf("%lld\n",(long long int) strlen(b));
	
	printf("%s","After exceution");
	
	

    free(a);
	free(b);
    return 0;
}