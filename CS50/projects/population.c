#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)

{
int m;
int n;
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

    // TODO: Calculate number of years until we reach threshold
    // assuming that every one year (n/4) is dead and (n/3) is born
    int z = (log((float)m/(float)n)) /log(19/12);

    // TODO: Print number of years
    printf("Years :%i\n", z);
}