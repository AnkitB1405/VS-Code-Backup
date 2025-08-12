#include<stdio.h>
#include<string.h>
struct student
{
    int rollno;
    char name[20];
    float percentage;
};
void main()
{
   struct student std;
   std.rollno = 0;
   strcpy(std.name, "xyz");
   std.percentage = 75.4;
   printf("student roll no is %d\n", std.rollno);
}