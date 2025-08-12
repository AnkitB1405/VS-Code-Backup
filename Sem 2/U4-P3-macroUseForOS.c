//Program to demonstrate the real use of conditional compilation and inbuilt or predefined macros
// see the output of gcc -E
// observe that only one block of code u can see on the terminal after preprocessing
#include<stdio.h>
int main()
{
	#ifdef __MINGW32__ // if mingw in windows system is used, the value of this macro is 1
		printf("windows system");
		char c,d;
		printf("enter the character");
		scanf("%c",&c);
		fflush(stdin);
		printf("enter one more character");
		scanf("%c",&d);
		printf("entered characters are %c %c",c,d);
	#elif __unix__	// if unix/Linux system is used, the value of this macro is 1
		char c;
		printf("unix system");
		#include<stdio_ext.h>
		printf("enter the character");
		scanf("%c",&c);
		__fpurge(stdin);  
		printf("enter one more character");
		scanf("%c",&d);
		printf("entered characters are %c %c",c,d);
	#elif __APPLE	// if MAC system is used, the value of this macro is 1
		printf("mac system");
	#else
		printf("other system");
	#endif
	return 0;
}