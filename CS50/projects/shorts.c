#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string word = get_string("Player 1: ");
    int b= 0;
    for (int i=0, n=strlen(word);i <= n; i++)
    {
      if(word[i]==' ' || word[i]=='\0')
      {
        b=b+1;
      }
    }  
    printf("%i\n",b);
}