#include <stdio.h>

int main()
{
// -------------------
	/*
	char ch;
	char* p_ch;
	printf("%d %d\n",sizeof(ch),sizeof(p_ch));
	int in;
	int* p_in;
	printf("%d %d\n",sizeof(in),sizeof(p_in));
	float fl;
	float* p_fl;
	printf("%d %d\n",sizeof(fl),sizeof(p_fl));
	long ln;
	long* p_ln;
	printf("%d %d\n",sizeof(ln),sizeof(p_ln));
	short sh;
	short* p_sh;
	printf("%d %d\n",sizeof(sh),sizeof(p_sh));
	*/
// -------------------
	/*
	char* p1;
	char * p2;
	char *p3;
	//all are valid format
	//char* p5,p6;
	//printf("%d %d\n",sizeof(p5),sizeof(p6));
	*/
// -------------------
	/*
	int a=3;
	int *p;
	printf("p=%d &p=%d *p=%d &a=%d\n",p,&p,*p,&a); // *p means content of 
	//p=&a;
	//printf("p=%d *p=%d\n",p,*p);
	*/

// -------------------
	/*
	int a[5]={11,12,13,14,15}; 
	int *ip;
	ip=a; // note it is not & as 'a' represents location of starting of array
	printf("at %d element = %d\n",ip,*ip); 
	//ip=ip+1; // move one step
	//printf("at %d element = %d\n",ip,*ip); 
	//ip=ip+2; // move two steps
	//printf("at %d element = %d\n",ip,*ip); 
	*/
// -------------------
	/*
	int a[5]={11,12,13,14,15}; 
	int *ip;
	ip=a; // note it is not & as 'a' represents location of starting of array
	for(int i=0;i<5;i++)
	{
	    printf("at %d element = %d\n",ip,*ip); 
	    ip++; // move one step
	}
	*/
// -------------------
	/*
	int a[5]={11,12,13,14,15}; 
	int *ip;
	ip=&a[4]; // note it is not & as 'a' represents location of starting of array
	for(int i=0;i<5;i++)
	{
	    printf("at %d element = %d\n",ip,*ip); 
	    ip--; // move one step
	}
	*/
// -------------------
	/*
	int a=3;
	int *p;
	p=&a;
	printf("p=%d *p=%d\n",p,*p);  
	//(*p)++;
	//printf("p=%d *p=%d\n",p,*p);  
	//p++;
	//printf("p=%d *p=%d\n",p,*p);  
	*/
// -------------------
	/*
	int a[5]={11,12,13,14,15}; 
	int *p;
	p=a; 
	printf("a=%d ip= %d\n",a,p); 
	//printf("a[0]=%d p[0]= %d\n",a[0],p[0]); 
	//printf("a[3]=%d p[3]= %d\n",a[3],p[3]); 
	//printf("*(a+2)=%d *(ip+2)= %d\n",*(a+2),*(p+2)); 
	//printf("3[a]=%d 3[p]= %d\n",3[a],3[p]); // is it surprising ?
	*/
// -------------------
	/*
	int a[5]={11,12,13,14,15}; 
	int *p;
	p=a; 
	for(int i=0;i<5;i++,p++)
	  printf("%d ",*p);
	//for(int i=0;i<5;i++,a++)
	//  printf("%d ",*a);
	*/


	return 0;
}