//An environment variable is a dynamic-named value that can affect the way running processes will behave on a computer.
//PATH
//CLASSPATH
//HOME

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
int main()
{
	char mypath[10000];
	//printf("%s\n", getenv("PATH"));
	char *path = getenv("PATH");
	printf("Before setting path is %s\n",path);
	strcpy(mypath, path);
	strcat(mypath, ":.");	// concatenating current directory to mypath

	// all paths are separated with : in ubuntu
	// all paths are separated with ; in windows
	//putenv() // for windows
	setenv("PATH", mypath, 1); // setting mypath back to PATH env
	// last parameter specifies whether to overwrite or not

	printf("\n");
	path = getenv("PATH");
	printf("After setting path is %s\n",path);
	printf("execution is over");
	return 0;
}
*/
/*
int main(int argc, char *argv[],char *envp[])
{
	
	/*printf("print only 10 envs\n");
	for(int i = 0;i<10;i++)
		printf("%s\n",envp[i]);
	*/	
		
		
	printf("printing ALL WITHOUT KNOWLING HOW MANY IT IS\n");
	extern char** environ; // stdlib.h must be included
	char **p = environ;
	int i = 0;
	while(*p != NULL)
	{
		//sleep(2);
		printf(" %d %s\n", i, *p);
		p++;
		i++;
		
	}	

	
	return 0;
}
*/