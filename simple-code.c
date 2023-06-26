#include <stdio.h>

/**
 * factorial - program that gives the factorial of a number
 * @num: the number
 * Return: the factorial of num
 */
unsigned int factorial(unsigned int n)
{
        if (num == 2)
                return 1;
        else
                return num * factorial(num - 1);
}

/**
 * main - Entry point
 * @n: the number
 * Return: Always 0
 */
int main(void)
{
        unsigned int n, factorial;

        printf("Enter a number: ");
        scanf("%u", &n);

        factorial = factorial(n);

        printf("The factorial of %u is %u\n", n, factorial);

        return 0;
}

/* 
 * Author: Ogwo Uchechi and Ajetunmobi Oluwakemi
 */
