#include<stdio.h>
#define PI 3.14 // symbolic constant, macro, plain text substitution
// It doesn't judge anything
// No memory is allocated for this

#define MAX 10
// name given to 10 is MAX. No memory is allocated for MAX. So &MAX is an error.
// Run this code using gcc -E and see the output of preprocessing stage. 
//MAX is replaced with 10 in preprocessing stage itself.

#define STR "Hello All" //#define can be used for strings as well

#define STRN 2+5*1 //macro with expression

#define SUM(a,b) a+b	 // SUM is not a function. It is a macro. 
//Processed in preprocessing stage

#define sqr(x) (x*x)		// change this to (x)*(x). 

#define cube(x) sqr(x)*x			// using sqr in cube

int main()
{
/*
	printf("%f",PI);

	//int a[MAX];
	//for(int i=0;i<MAX;i++)
	  //printf("%d ",a[i]);

	//printf("The string is %s\n",STR);		// The string is Hello All

*/
/*
	printf("Value is %d\n",STRN);		// Value of expression

	//int a,b;
	//printf("Enter two numbers:\n");
	//scanf("%d%d",&a,&b);
	//printf("The sum of two numbers is %d\n",SUM(a,b));


	//printf("%d",sqr(2+3));	

	//printf("The cube of 9 is %d\n",cube(9));
*/
/*
	//MAX=20;		// Error	

	printf("MAX is %d",MAX);		

	if(MAX==20)
	  printf("hello\n");
	else
	{
	  printf("U here \n");
	  #define MAX 30		// warning but no error
	}
	printf("MAX is %d",MAX);		
*/
/*
	printf("file name is %s",__FILE__);		// current file name
	printf("\nDate is %s",__DATE__);		// current date
	printf("\nTime is %s",__TIME__);		// current time during preprocessing
	printf("\nC version is %d",__STDC_VERSION__); 
	//This macro expands to the C Standard’s version number, a long integer constant of the form yyyymmL where yyyy and mm are the year and month of the Standard version
	//Example: 199901L signifies the 1999 revision of the C standard
	
	printf("\nC version is %d",__STDC__); 	//In normal operation, this macro expands to the constant 1, to signify that this compiler conforms to ISO Standard C
*/
/*	
/*	printf("\nLine number is %d",__LINE__);		
	if(__LINE__==12)		
		printf("hello");
*/
/*

	#ifdef MAX	//No parentheses for #ifdef
		printf("MAX  defined\n");	// If #define above is removed, this line is not included for compilation.
	#else
		printf("not defined\n");
	#endif	// compulsory for #ifdef 
	printf("Outside the scope of #ifdef\n");
*/
/*

	#ifndef MAX	//No parentheses for #ifdef
		printf("MAX  not defined\n");	// If #define above is removed, this line is not included for compilation.
	#else
		printf("Max defined\n");
	#endif	// compulsory for #ifdef 
	printf("Outside the scope of #ifdef\n");
*/

/*
	printf("Hello World\n");
	#if 0
	printf("I am fine\n");
	#endif
*/
/*
	#undef MAX
	#ifdef MAX	//No parentheses for #ifdef
		printf("MAX  defined\n");	// If #define above is removed, this line is not included for compilation.
	#else
		printf("not defined\n");
	#endif	// compulsory for #ifdef 
	printf("Outside the scope of #ifdef\n");
*/

	return 0;
}