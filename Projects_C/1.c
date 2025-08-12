#include <stdio.h>
int main()
{
double income, tax = 0;
printf("Enter your annual income: ");
scanf("%lf", &income);
if (income < 0)
{
printf("Invalid income entered!\n");
}
else
{
if (income > 1000000)
{
tax += (income - 1000000) * 0.30; // 30% tax on amount exceeding ₹10,00,000
tax += 500000 * 0.20; // 20% tax on previous ₹5,00,000
tax += 250000 * 0.05; // 5% tax on ₹2,50,000
}
else if (income > 500000)
{
tax += (income - 500000) * 0.20; // 20% tax on amount exceeding ₹5,00,000
tax += 250000 * 0.05; // 5% tax on ₹2,50,000
}
else if (income > 250000)
{
tax += (income - 250000) * 0.05; // 5% tax on amount exceeding ₹2,50,000
}
printf("Income Tax: %.2lf\n", tax);
printf("Net Income after Tax: %.2lf\n", income - tax);
}
return 0;
}