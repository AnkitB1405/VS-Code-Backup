#include <stdio.h> 
#include <string.h>

int main(void) 
{ 
    int x;
    char a[100];
    printf("Enter the string\n");
    scanf(" %[^\n]",a);

    char b[50];
    strcpy(b,a);
    printf("%s\n%s\n",a,b);
    printf("string length of a and b %d %d\n",strlen(a),strlen(b));
    printf("sizeof a and b %d %d\n",sizeof(a),sizeof(b));

    //char c[50]="How are you";
    //strcat(a,c);
    //printf("%s\n%s\n",a,c);
    //printf("string length of a and c %d %d\n",strlen(a),strlen(c));
    //printf("sizeof a and c %d %d\n",sizeof(a),sizeof(c));

    //strcpy(a,"Hello World");
    //char d[50]="Hello World";
    //x=strcmp(a,d);  // 0=equal, 1=a is lexicographically higher -1= lower
    //printf("x = %d\n",x);

    //char *p;
    //p=strchr(a,'l');
    //printf("p = %d and *p = %c\n",p,*p);


    // write your own implementation of all the functions

    return 0; 
}
