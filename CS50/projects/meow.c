#include <stdio.h>
#include <cs50.h>
void meow(int);
int main(void)
    {    

        meow(4);
        
    }    
void meow(int n)
    {
         for(int i=0; i<n; i++)
         {
          printf("meow\n");
         }
    }
    