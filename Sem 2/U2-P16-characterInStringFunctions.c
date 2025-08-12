#include<stdio.h>
char* my_strchr(char a[],char ch);
int main()
{
	char str1[20];
	char ch;
	printf("Enter the string\n");
	scanf("%s",str1);
	fflush(stdin);
	printf("Enter the character\n");
	scanf("%c",&ch);
	char *res = my_strchr(str1, ch);
	if (res != NULL)
		printf("first %c is available in %p address and position is %d",ch,res, res-str1);
	else
		printf("character not available in string\n");

	return 0;
}

char* my_strchr(char a[],char ch)
{
	char *p = NULL;
	char *s = a;
	while(*s != '\0' && p==NULL)
	{
		if(*s == ch)
			p = s;
		s++;
	}
	return p;
}