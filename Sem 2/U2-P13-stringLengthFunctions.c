#include<stdio.h>
int my_strlen(char a[]);
int main()
{
	char a[100];
	printf("Enter the string\n");
	scanf(" %[^\n]",a);
	printf("length is %d\n",my_strlen(a));
	return 0;
}
int my_strlen(char a[])
{
	/*
	int i = 0;
	while(a[i] != '\0')
	i++;
	return i;
	*/

	/*
	int i = 0;
	while(*a)
	{
		i++;
		a++;
	}
	return i;
	*/


	// using recursion

	/*if(!(*a))
		return 0;
	else	return 1+my_strlen(++a);  //pass (a+1)
	*/ 
	/*
	if(!(*a))
		return 0;
	else	return 1+my_strlen(a++);
	*/




	// using a local pointer
	char *a_copy;
	a_copy = a;
	while(*a_copy)
		a_copy++;
	return a_copy - a;
	

}