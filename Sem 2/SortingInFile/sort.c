#include"sort.h"
#include<stdio.h>
#include<string.h>
void init_ptr(struct student s[], struct student *p[], int n)
{
		for(int i = 0; i < n; ++i) 
		{ 
			p[i] = &s[i]; 
		}

}
void swap( struct student** lhs,  struct student** rhs) 
{ 
	struct student* temp = *lhs; 
	*lhs = *rhs; 
	*rhs = temp; 
} 

void disp(struct student* p[], int n) 
{
	for(int i = 0; i < n; ++i) 
	{
		//printf("%s %d\n", (s+i)->name, (s+i)->roll); 
		printf("%d %s\n", p[i]->roll, p[i]->name); 
	}
} 
void selection_sort_roll_no(struct student *s[],int n)
{
	int i,pos,j;
	for(i = 0;i<n-1;i++)
	{
		printf("in for\n");
		pos = i;
		for(j = i+1;j<n;j++)
		{
			if((s[pos]->roll) > (s[j]->roll))
				pos = j;
		}
		if(pos != i)
			swap(&s[pos],&s[i]);
	}
}

void selection_sort_names(struct student* s[],int n)
{
	int i,pos,j;
	for(i = 0;i<n-1;i++)
	{
		pos = i;
		for(j = i+1;j<n;j++)
		{
			if(strcmp(s[pos]->name,s[j]->name)>0)
				pos = j;
		}
		if(pos != i)
			swap(&s[pos],&s[i]);
	}
}
