#include <stdio.h>

int main()
{
// -------------------
	/*
	int a[5] = {1, 2, 3, 4, 5};
	printf("%d \n",a[0]); // accessing one element
	for(int i=0;i<5;i++)
	  printf("%X ",a[i]); // array range starts from 0
	printf("\n");
	//all  values are junk. If it is 0 then also not assured everytime.
	*/
// -------------------
	/*	
	int a[5];
	for(int i=0;i<3;i++)
	  a[i]=10+i;  // initialising 3 elements
	for(int i=0;i<5;i++)
	  printf("%d ",a[i]); // first 3 are as per initialization, rest junk
	printf("\n");
	*/
// -------------------
	/*
	int a[5];
	printf("Give values for the array elements one by one\n");	
	for(int i=0;i<3;i++)
	  scanf("%d",&a[i]);  // initialising 3 elements from user input
	for(int i=0;i<5;i++)
	  printf("%d ",a[i]); // first 3 are as per initialization, rest junk
	printf("\n");
	*/
// -------------------
	/*
	int a[5]={11,22,33,44,55}; // initialisation during decleration
	for(int i=0;i<5;i++)
	  printf("%d ",a[i]); 
	printf("\n");
	*/
// -------------------
	/*
	int a[5]={11,22,33}; // partial initialisation during decleration
	for(int i=0;i<5;i++)
	  printf("%d ",a[i]); // first 3 are as per initialization, rest junk
	printf("\n");
	*/
// -------------------
	/*
	int a[5]={11,22,33,44,55,66,77}; // initialisation with extra data. Undefined behaviour
	for(int i=0;i<5;i++)
	  printf("%d ",a[i]); // all 5 are initialsed
	printf("\n");
	*/
// -------------------
	/*
	int a[5]={[1]=51,[3]=53}; // specific initialisation during decleration
	for(int i=0;i<5;i++)
	  printf("%d ",a[i]); // only specific are initialized, rest junk
	printf("\n");
	*/
// -------------------
	/*
	int a[]={1,2,3}; // size of array is decided automatically based on number of data
	for(int i=0;i<5;i++)
	  printf("%d ",a[i]); // first 3 are as per initialization, rest junk
	printf("\n");
	printf("Number of element in a = %d\n",sizeof(a)/sizeof(int));
	*/
// -------------------
	/*
	int a[5]={11,12,13,14,15}; 
	for(int i=0;i<5;i++)
	  printf("a[%d] at 0x%X value %d\n",i,&a[i],a[i]); // location and content
	*/
// -------------------
	/*
	int a[5]={11,12,13,14,15}; 
	for(int i=0;i<5;i++)
	  printf("%d ",&a[i]); // locations
	printf("\n");
	printf("a= %d\n",a);  // a represents address of first location not content of first location
	*/
// -------------------
	/*
	int a[5]={11,12,13,14,15}; 
	for(int i=4;i>=0;i--)
	  printf("%d ",a[i]); // order of access does not matter
	printf("\n");
	printf("a[3] =%d\n",a[3]);	
	printf("a[0] =%d\n",a[0]);	
	*/



	return 0;
}