#include<stdio.h>
char a[100];
char* input_func(char a[])
{
    printf("Enter the string\n");
    scanf(" %[^\n]",a);
    return a;
}
char* extract_sentences(char a[],int i)
{
    char b[50];
    while(a[i] != '.',a[i] != '?',a[i] != '!')
    {
        b[i] = a[i];
        i++;
    }
    b[i] = '\0';
    printf("%s\n",b);
}
char* extract_questions(char a[])
{
    int i = 0;
    while(a[i] != '\0')
    {
        if(a[i] == '?')
        {
            extract_sentences(a,i);
        }
        i++;
    }
    return a;
}
int main()
{
    input_func(a);
    printf("%s",a);
    extract_questions(a);
    return 0;
}