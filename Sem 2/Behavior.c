#include<stdio.h>
int main()
{
	//printf("%d %f %d %f\n",5,5.5,5.5,5);	// Undefined behavior
	//printf("%d\n",5/0);	// Undefined behavior
	//printf("value is %s\n","50");      // proper output
	//printf("value is %s\n",50);        //undefined behavior
// -------------------
	printf("%d %d %d\n",sizeof(int),sizeof(short int),sizeof(float));	// Implementation defined behavior
// -------------------
	int d = 10;
	//printf("%d %d %d\n", d++, d++);, d++ - );
	//printf("%d\n", d++ - ++d);	// Unspecified behavior

	return 0;
}
