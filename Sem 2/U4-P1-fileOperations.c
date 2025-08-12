
#include<stdio.h>
#include<stdlib.h>
#include <errno.h>
#include<string.h>



void main()
{
/*
  printf("Hello World\n"); //output can be directed to a file using > ( write) >> (append)
*/
/*
  char ch;
  ch=getchar(); // uses standard input output
  putchar(ch);

  //ch=getc(stdin); // standard input mentioned as stream parameter 
  //putc(ch,stdout);

  //ch=fgetc(stdin); // similar but there are some similar named functions for other operation
  //fputc(ch,stdout);

*/  
/* 
  char ch;
  FILE* fp;

  fp = fopen("data.txt", "r");
  printf("fp = %X\n",fp);

  if(fp == NULL)
     printf("cannot open the file");
  else
  {
   //ch = getc(fp);
   ch = fgetc(fp);
   while (ch != EOF)
   {
     putc(ch, stdout);// ch on the terminal
     ch = getc(fp); //fp moves automatically to next element without explicit ++
   }
   fclose(fp); //close the opened file
  }
  //printf("Value of EOF is %d\n",EOF);
*/
/*
  FILE* fp;
  if (fp = fopen("data.txt", "r"))
  {
   char line[500];
   //while (fscanf(fp,"%s",line)!= EOF) //does not include \n as it is used as terminator of scan
   while (fgets(line,100,fp)!= NULL) //\n included. fgets returns NULL if an error occurs or the end-of-file is reached
   {
     printf("%s",line);
   }
   fclose(fp);
  }
*/
/*
  FILE* fp;
  char line[100]="This is a new line\n";
  int i=0;
  if (fp = fopen("out.txt", "w")) //if file does not exist it will be created for "w" or "a"
  {
   while (line[i] != '\0')
   {
     putc(line[i], fp); // character by character writing
     i++;
   }
   fclose(fp);
  }
*/
/*
  FILE* fp;
  int x=10,y;
  char line[100];
  if (fp = fopen("out.txt", "w"))
  {
    fprintf(fp,"value of x = %d\n",x);
    fprintf(fp,"%d",x);
    fclose(fp);
  }
  if (fp = fopen("out.txt", "r"))
  {
    fscanf(fp,"%[^\n]s",line);
    fscanf(fp,"%d",&y);
    printf("%s\n",line);
    printf("%d\n",y+1);
    fclose(fp);
  }

*/
/*
  FILE *fp1 = fopen("data.txt","r");
  FILE *fp2 = fopen("out.txt","w"); // instead "w" change to "a" and observe the output file
  char line[500];
  if(fp1==NULL || fp2 ==NULL)
    printf("issue in opening the file\n");
  else
  {

    while(fgets(line,500,fp1) != NULL)  
    {
      fputs(line, stdout);
      fputs(line, fp2);
    }
  }

*/
/*
  FILE* fp;
  char line[100]="This is a line for test";
  char read_buf[100];
  int n;

  fp = fopen("out.txt", "w");
  if(fp == NULL)
  {
    printf("File does not exist\n");
    return;
  }

  n=fwrite(line,1,sizeof(line),fp);  //write chunk of data of bytes to file for each case 
  //n=fwrite(line,sizeof(line),1,fp); 
  //n=fwrite(line,1,strlen(line),fp);  
  //n=fwrite(line,strlen(line),1,fp); 

  //function parameters : size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
  //ptr : pointer to the block of memory or the array from where the elements are to be copied
  //size : size of each element in bytes which are to be written
  //count : specifies the number of elements that are to be written
  //stream : pointer to a FILE object, where the data read will be written  

  printf("Number of elements written = %d\n");

  fclose(fp);

  fp = fopen("out.txt", "r");
  n=fread(read_buf,1,sizeof(read_buf),fp);

  printf("%s\n",read_buf);
  printf("Number of elements read = %d\n");
  fclose(fp);
  
*/
/*
  FILE* fp;
  int num[10]={10,11,20,21,30,31,40,41,50,51};
  int r;

  fp = fopen("out.txt", "w");
  if(fp == NULL)
  {
    printf("File does not exist\n");
    return;
  }

  fwrite(num,10,sizeof(int),fp);   

  //for(int i=0;i<10;i++)
   //fwrite(&num[i],1,sizeof(int),fp);   

  fclose(fp);

  fp = fopen("out.txt", "r");
  for(int i=0;i<10;i++)
  {
    fread(&r,1,sizeof(int),fp);
    printf("%d ",r);
  }
  fclose(fp);

*/
/*
  struct student
  {
    int roll;
    char name[50];
    short int sem;
    char sec;
  };
  
  FILE *fp;
  struct student x={5,"Amit",2,'X'};
  struct student y;
  struct student* p;

  if (fp = fopen("info.txt", "w"))
  {
   fwrite(&x,1,sizeof(struct student),fp);
   fclose(fp);
  }
  if (fp = fopen("info.txt", "r"))
  {
   fread(&y,1,sizeof(struct student),fp);
   printf("roll = %d ",y.roll);
   printf("Name = %s ",y.name);
   printf("Semester = %d ",y.sem);
   printf("Sec = %c \n",y.sec);
   fclose(fp);
  }
*/

/*
  FILE *fp = fopen("data.txt","r");
  if(fp == NULL)
     printf("cannot open the file");
  else
  {
     printf("\nCurrent location = %d\n",ftell(fp)); //starting location
     putc(getc(fp), stdout);
     printf("\nCurrent location = %d\n",ftell(fp)); // automatically moved by getc

     //fseek(fp,3,SEEK_CUR); // move with respect to current location 
     //printf("\nCurrent location = %d\n",ftell(fp));
     //putc(getc(fp), stdout);

     //fseek(fp,2,SEEK_SET); // move from start location
     //printf("\nCurrent location = %d\n",ftell(fp)); 
     //putc(getc(fp), stdout);

     //fseek(fp,-2,SEEK_END); // move from end location
     //printf("\nCurrent location = %d\n",ftell(fp)); 
     //putc(getc(fp), stdout);

     //rewind(fp);
     //printf("\nCurrent location = %d\n",ftell(fp)); 
		
    fclose(fp);
  }
*/
/*
  FILE *fp;

  fp = fopen ("data.txt", "r");  
  fprintf(fp,"%s","Hello World");
  if (ferror(fp))
  printf("Error in writing to file\n");
  fclose(fp);

  //fp = fopen ("File.txt", "r");  // No such file
  //printf("Value of errno: %d %s\n ", errno, strerror(errno));
  //perror("Bad code");

*/
/*
  FILE *fp=fopen("matches.csv","r");
  char line[500];
  if(fp==NULL)
  {
    printf("error in opening the file\n");
  }
  else
  {
    //fgets(line,500,fp);
    fgets(line,500,fp);
    char *val;    
    val=strtok(line,",");
    printf("%s\n",val);
    val=strtok(NULL,",");
    printf("%s\n",val);
    val=strtok(NULL,",");
    printf("%s\n",val);
    //val=strtok(NULL,"/"); // 2nd line onwards extract month
    //printf("%s\n",val);
   }
*/
/*
  FILE *fp=fopen("matches.csv","r");
  char line[500];
  if(fp==NULL)
  {
    printf("error in opening the file\n");
  }
  else
  {
    int count=0;
    while(fgets(line,500,fp)!=NULL)
    {		
      char *val=strtok(line,",");
      val=strtok(NULL,",");
      if(strcmp(val,"2008")==0)
      {
	count++;
      }
    }
    fclose(fp);
    printf("Number of matches in 2008 are %d\n",count);
  }
*/	

}

