#include <stdio.h>
#include <cs50.h>
float average(int length, int array[]);
int main(void)
{
    
    int total = get_int("total numbers of scores is: ");
    
    int score[total];
    for(int i = 0;i < total ; i++ )
    {
    score[i]=get_int("score: ");
    }
    
    printf("average: %f\n", average(total,score));

    
}
float average(int length, int array[])
{
    int sum=0;
    for(int i =0; i < length; i++)
    {
    sum+= array[i]; 
    }
    return sum / (float)length ;
}