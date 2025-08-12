#include<stdio.h>
int main()
{
int a, sum =0;
printf("Enter the number of elements: ");
scanf("%d",&a);
printf("\n");
int arr[a];
printf("Enter the elements: ");
for (int i = 0; i<a; i++)
{
scanf("%d", &arr[i]);
sum += arr[i];
}
printf("\nThe sum of elements is: %d\n", sum);
}
