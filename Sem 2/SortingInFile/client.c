#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"sort.h"
int main()
{
	FILE *fr=fopen("student1.csv","r");
	char a[200];
	fgets(a,200,fr);
	//printf("%s",a);
	char *item;
	struct student s[100];
	int i=0;
	while(fgets(a,200,fr))
	{
		item=strtok(a,",");
		s[i].roll=atoi(item);
		item=strtok(NULL,",");
		strcpy(s[i].name,item);
		i++;
		
	}
	int n = i;
	fclose(fr);
	struct student *p[100];
	init_ptr(s, p, n);
	disp(p,n);
	
	
	int ch;
	printf("enter the choice.\n 1.sort on roll\n");
	printf("2. sort on name");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:selection_sort_roll_no(p,n);
				disp(p,n);
				break;
		case 2:selection_sort_names(p,n);disp(p,n);break;
			   
		default: printf("exiting from the program");
				exit(0);
		
	}	
	FILE *fw=fopen("student_sorted.csv","w");
	fprintf(fw,"Roll_number,Name\n");
	i=0;
	while(i<n)
	{
		fprintf(fw,"%d,%s",p[i]->roll,p[i]->name);
		i++;
	}
	fclose(fw);
	printf("sorted data is written to a file student_sorted.csv\n");
		
	return 0;
}
