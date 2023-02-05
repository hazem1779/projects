#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main (void)
{
    float dollars;

    do
    {
        dollars= get_float("Change owned:");
    }
    while(dollars<0);

    int n= round(dollars*100);
    int i=0;
    while (n>=25)
    {
        n=n-25;
        i=i+1;
    }
     while (n>=10)
    {
        n=n-10;
        i=i+1;
    }
     while (n>=5)
    {
        n=n-5;
        i=i+1;
    }
     while (n>=1)
    {
        n=n-1;
        i=i+1;
    }
    printf("%i\n",i);
}