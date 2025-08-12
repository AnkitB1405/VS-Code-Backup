#include<stdio.h>
void my_strcpy(char[],char []);
int main()
{
	char str1[50];
	char str2[50];// str2 must be big enough to store str1
	printf("enter the string\n");
	scanf("%s",str1);
	my_strcpy(str2,str1);
	printf("str1 and str2 are %s and %s\n",str1,str2);
	return 0;
}
/*void my_strcpy(char a[],char b[])
{
	int i = 0;
	while(b[i] != '\0')
	{
		a[i] = b[i];
		i++;	
	}
	//a[i] = b[i]; // error if this statement not added
}
*/
/*
void my_strcpy(char a[],char b[])
{
	while(*b != '\0')
	{
		*a = *b;
		a++;b++;	
	}
	*a = *b;// here also same case
}
*/
/*
void my_strcpy(char a[],char b[])
{
	while((*a = *b) != '\0')
	{
		a++;b++;	
	}
	
}
*/
/*void my_strcpy(char a[],char b[])
{
	while(*a++ = *b++);
	
	
}
*/


