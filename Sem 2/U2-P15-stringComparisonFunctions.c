#include<stdio.h>
int my_strcmp(char*,char*);
int main()
{
	char str1[20];
	char str2[20];
	printf("enter two strings\n");
	scanf("%s",str1);
	scanf("%s",str2);	
	int res = my_strcmp(str1,str2);
	printf("%d----\n",res);
	if(!res)
		printf("equal\n");
	else
		printf("not equal\n");
	return 0;
}

int my_strcmp(char* a,char* b)
{
	int i;
	for(i = 0;b[i] != '\0' && a[i] != '\0' && a[i] == b[i];i++);
	return a[i] - b[i];
		
}

/*
int my_strcmp(char* a,char* b)
{

	for(;*b && *a && *a == *b;a++,b++);
	return *a - *b;
		
}
*/
