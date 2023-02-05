#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
void cipher_code(string word, string sub);

int main(int argc, string argv[] )
{
    char dup[26];
    
    if(argc != 2)
    {
        printf("MISSING COMMAND-LINE ARGUMENT!\n") ;
        return 1 ;
    }
     int N = strlen(argv[1]);

     if(argc == 2 && N != 26 )
    {
        printf("KEY MUST BE 26 ALPHABET CHARACTERS!\n") ;
        return 1 ;
    }
     else if(argc == 2 && N == 26 )
    {
       
        for (int i=0 ;i < N ; i++)
        {
         dup[i]= argv[1][i] ;    
         if (argv[1][i] < 'A' || (argv[1][i] > 'Z' && argv[1][i] < 'a') || argv[1][i] > 'z' )
         {
         printf("KEY MUST BE 26 ALPHABET CHARACTERS!\n") ;
         return 1 ;
         }
         
        }
    }
    
  
    for (int i=0 ;i < N ; i++)
    {
        int x=0;
     for (int I=0 ;I < N ; I++)
     {
        if(dup[i]==argv[1][I])
        {
          x=x+1;
        }
     }
       if (x  != 1 )
      {
         printf("DUBLICATED! %c\n",x);
         return 1 ;
      }
    }
  
    string word1= get_string("plaintext:  ");
    cipher_code(word1,argv[1]);
    //printf("ciphertext: %s\n", cipher);
}
void cipher_code(string word, string sub)
{
 int W = strlen(word);
 int S = strlen(sub);
 char bdan[W];

  for (int i=0 ;i < W; i++)
  {
   if(word[i]>= 'a' && word[i]<='z')
      {
         int V= 0 ;

        for ( char J= 'a'  ; J <= 'z'  ; J=(int)J+1 )
             {
             if (word[i] == J)
                {
                bdan[i]=tolower(sub[V]);
                }
            else
               {
                V++ ;
               }
             }
      }
     else if (word[i]>= 'A' && word[i]<='Z')
      {
      int B= 0 ;
  for ( char H= 'A'  ; H <= 'Z'  ; H=(int)H+1 )
    {
    if (word[i] == H)
        {
     
      
         bdan[i]=toupper(sub[B]);
        }
    else
        {
        B++ ;
        }
   }
       }
       else
       {
         bdan[i]=word[i] ;  
       }
   
}
  printf("ciphertext: %s\n", bdan);
}


