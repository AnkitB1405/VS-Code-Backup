// Binary search:
/*	works on sorted collection of elements.
	Time required to access each element in the collection must be same - constant time
	*/

#include<stdio.h>
int mysearch(int a[],int low,int high,int key)
{
	/* binary search - iterative solution
	int pos = -1;
	int found = 0;
	// if found variable is not created, what is the problem. Think about it?
	// please write the diagram
	while(low<=high && found ==0)
	{
		int mid = (low+high)/2;
		if(a[mid]==key)
			{
			pos = mid;found = 1;
			}
		else if(key<a[mid])
			high = mid-1;
		else
			low = mid+1;
	}
	return pos;	
	*/
	//   recursive solution
	if(low > high)	// base condition
		return -1;
	else
	{
		int mid = (low+high)/2;
		if(a[mid]==key)
		{
			return mid;
		}
		else if(key<a[mid])
			return mysearch(a,low,mid-1,key);
		else
			return mysearch(a,mid+1,high,key);
	}
}

int main()
{
	int a[100];
	int key; int n; int i;
	FILE *fp = fopen("numbers.txt","r");
	printf("How many numbers you want to read from the file?");
	scanf("%d",&n);
	for(i = 0;i<n;i++)
		fscanf(fp,"%d",&a[i]);
	fclose(fp);
	
	printf("enter the elements to be searched\n");
	scanf("%d",&key);
	int res = mysearch(a,0,5,key);
	if(res == -1)
		printf("not found");
	else
		printf("found at %d\n",res);
}