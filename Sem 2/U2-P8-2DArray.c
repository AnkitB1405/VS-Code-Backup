#include <stdio.h>

int main()
{
// -------------------
	/*
	int a[3][2] ={{11,22},{33,44},{55,66}};
	printf("%d\n",a[0][0]);
	printf("%d\n",a[2][1]);
	for(int r=0;r<3;r++)
	{
	  for(int c=0;c<2;c++)
	  {
	    printf("%d ",a[r][c]);
	  }
	  printf("\n");
	}
	//printf("%d\n",a[1][2]);
	*/

// -------------------
	/*
	int a[3][2] ={11,22,33,44,55,66};
	for(int r=0;r<3;r++)
	{
	  for(int c=0;c<2;c++)
	  {
	    printf("%d ",a[r][c]);
	  }
	  printf("\n");
	}
	printf("sizeof(a)=%d\n",sizeof(a));
	printf("sizeof(a[0])=%d\n",sizeof(a[0]));
	*/

// -------------------
	/*
	int a[][2] ={11,22,33,44,55,66,77};// 7 elements
	int rows=sizeof(a)/sizeof(a[0]);
	printf("rows = %d\n",rows);
	for(int r=0;r<rows;r++)
	{
	  for(int c=0;c<2;c++)
	  {
	    printf("%d ",a[r][c]);
	  }
	  printf("\n");
	}
	*/
// -------------------
	/*
	int a[][2] ={{11,22},{33},{44,55},{66,77}};// 7 elements
	int rows=sizeof(a)/sizeof(a[0]);
	printf("rows = %d\n",rows);
	for(int r=0;r<rows;r++)
	{
	  for(int c=0;c<2;c++)
	  {
	    printf("%d ",a[r][c]);
	  }
	  printf("\n");
	}
	//printf("%d\n",sizeof(a[0]));
	//printf("%d\n",sizeof(a[1]));

	//printf("%d\n",sizeof(a[1]+2)); //not valid
	//char x[5]={1,2,3,4,5};
	//printf("%d\n",sizeof(x)); //valid
	//printf("%d\n",sizeof(x+3)); // not valid
	*/

// -------------------
	//
	char a[3][2] ={11,22,33,44,55,66};
	for(int r=0;r<3;r++)
	{
	  printf("&a[%d]=%X\n",r,&a[r]);
	  for(int c=0;c<2;c++)
	  {
	    printf("&a[%d][%d]=%X\n",r,c,&a[r][c]);
	  }
	  printf("\n");
	}
	printf("Address of each element\n");
	printf("%X %X %X\n",a,a+1,a+2);//address of each element

	//printf("\nSize of each element\n");
	//printf("%d\n",sizeof(*a));//size of each element which shows that each element is an array

	printf("\nContent of each element\n");
	printf("%X %X %X\n",*a,*(a+1),*(a+2));//content of each element is start address of each array

	//printf("\nAddress of each element of sub array of first element\n");
	//printf("%X %X\n",*a,*a+1);//address of each element of first sub array of first element

	//printf("\nsizeof of each element of sub array of first element\n");
	//printf("%X %X %X\n",sizeof(a),sizeof(*(a)),sizeof(*(a+1)));//sizeof total array and sizeof first and second sub array 

	//printf("%X %X\n",sizeof(a+1),sizeof(*(a+1)));
	//first one is invalid but the second one is fine as it is a sub array

	//printf("\nAddress of each element of sub array of second element\n");
	//printf("%X %X\n",*(a+1),*(a+1)+1);
	//address of each element of sub array of second element

	//printf("\nConent of each element of sub array of first element\n");
	//printf("%d %d\n",*(*a),*(*a+1));
	//address of each element of first sub array of first element

	//printf("\nConent of each element of sub array of second element\n");
	//printf("%d %d\n",*(*(a+1)),*(*(a+1)+1));
	//address of each element of sub array of second element
	//

// -------------------
	/*
	char a[3][2] ={11,22,33,44,55,66};
	for(int r=0;r<3;r++)
	{
	  for(int c=0;c<2;c++)
	  {
	    printf("%d ",*(*(a+r)+c));
	  }
	  printf("\n");
	}
	*/

// -------------------
	/*
	char a[3][2] ={11,22,33,44,55,66};
	printf("%d\n",sizeof(a));
	char *p=a; // ignore the waring for the time being
	for(int i=0;i<sizeof(a);i++)
	{
	  printf("%d ",*p);
	  p++;
	}
	*/

// -------------------
	/*
	char a[3][2] ={11,22,33,44,55,66};
	char *p[3]; // array of pointers
	p[0]=a[0];
	p[1]=a[1];
	p[2]=a[2];
	printf("First Row\n");
	for(int c=0;c<sizeof(a[0]);c++)
	{
	  printf("%d ",*p[0]);
	  p[0]++;
	}

	p[0]=a[0];
	p[1]=a[1];
	p[2]=a[2];
	printf("\nMatrix\n");
	for(int r=0;r<3;r++)
	{
	  for(int c=0;c<2;c++)
	  {
	    printf("%d ",*p[r]);
	    p[r]++;
	  }
	  printf("\n");
	}
	*/

// -------------------
	/*
	char a[3][2] ={11,22,33,44,55,66};
	char *p[3]; // array of pointers
	p[0]=a[2];
	p[1]=a[0];
	p[2]=a[1];
	printf("Matrix\n");
	for(int r=0;r<3;r++)
	{
	  for(int c=0;c<2;c++)
	  {
	    printf("%d ",*p[r]);
	    p[r]++;
	  }
	  printf("\n");
	}
	*/
// -------------------
	/*
	char a[2][3][2]={  { {5, 10}, {6, 11}, {7, 12} }, { {20, 30}, {21, 31}, {22, 32} }   }; //2 tables 3 rows 2 coloumns.
	printf("a[0][2][1]=%d\n",a[0][2][1]);
	*/
// -------------------
	/*
	char a[10][5][3][2]; // change data type and observe
	printf("sizeof(a)=%d\n",sizeof(a));
	//printf("sizeof(*a)=%d\n",sizeof(*a));
	//printf("sizeof(*(*a))=%d\n",sizeof(*(*a)));
	//printf("sizeof(*(*(*a)))=%d\n",sizeof(*(*(*a))));
	//printf("sizeof(*(*(*(*a))))=%d\n",sizeof(*(*(*(*a)))));
	*/

	return 0;
}
