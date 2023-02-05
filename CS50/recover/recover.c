#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t byte;
int i=0;
int main(int argc, char *argv[])
{
  if (argc != 2)
    {
        printf("Usage: ./recover memory\n");
        return 1;
    }

  FILE *input = fopen(argv[1],"r"); 
  char name[8];
  sprintf(name,"%03i.jpg",i) ;
  FILE *image = fopen(name,"w"); 
  
   byte block[512];
 
   while (fread(block, sizeof(byte), 512, input))
 {
    if(block[0]== 0xff && block[1]== 0xd8 && block[2]== 0xff  && (block[3] & 0xf0)==0xe0)
    {
      if(i==0)
      {
       fwrite(block,sizeof(byte),512,image);
       i++;
      }
      else if(i>0)
      {
      
      sprintf(name, "%03i.jpg",i) ;
      image = fopen(name,"w"); 
      fwrite(block,sizeof(byte),512,image);
      i++;
      }
    }
    else if(i>0)
    {
      fwrite(block,sizeof(byte),512,image);
    }
 }

}