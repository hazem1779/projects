#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
 
int count_letters(string word);
int count_words(string word);
int count_sentences(string word);
int calculate_grade(int l, int w, int s);


int main(void)
{
    string text = get_string("Text: ") ;
    int letters= count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int grade = calculate_grade(letters, words, sentences);
    
    if (grade <= 0)
    {
      printf("Before Grade 1\n");  
    }
    else if (grade < 16)
    {
        printf("Grade %i\n", grade );
    }
    else 
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string word)
{
    int n=strlen(word);
    int B=0;
   for (int i=0 ; i <=n; i++)
   {
       if( (word[i] >= 'A' && word[i] <='Z') || (word[i] >= 'a' && word[i] <= 'z') )
       {
           B=B+1;
       }
   }
   return B ;
}
int count_words(string word)
{
    int b= 0;
    for (int i=0, n=strlen(word);i <= n; i++)
    {
      if(word[i]==' ' || word[i]=='\0')
      {
        b=b+1;
      }
    }  
   return b ;
}
int count_sentences(string word)
{
    int b= 0;
    for (int i=0, n=strlen(word);i <= n; i++)
    {
      if(word[i]=='.' || word[i]=='!' || word[i]=='?' )
      {
        b=b+1;
      }
    }  
   return b ;
}
int calculate_grade(int l, int w, int s)
{
   float letters= (l*100) / (float)w ;
   float sentences= (s*100) / (float)w ;
   float index= 0.0588 *  letters - 0.296 * sentences - 15.8 ;
   int I = round (index);
   return I ;
  
}