#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int m;
    int n;  
    int i = 0;

    // TODO: Prompt for start size


    do
    {
        n =get_int ("Start number:");
    }
    while (n<9);


    // TODO: Prompt for end size
    do
    {
        m = get_int ("End number:");
    }

    while (m<n);
  // calculations
    int z;
    while (m>n)
    {
        z=n+n/3-n/4;
        n=z;
        i=i+1;
    }
     printf("Years: %i\n",i);
    }