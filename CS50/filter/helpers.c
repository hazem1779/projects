#include "helpers.h"
#include <stdio.h>
#include <math.h>
//void sobel_operator(RGBTRIPLE b[3][3] , RGBTRIPLE image);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int i=0; i<=height-1; i++)
    {
        for(int j=0; j<=width-1; j++)
        {
            average =  (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0  ;
            average= round(average) ;

        if (average > 255)
        {
            average = 255;
        }

            image[i][j].rgbtBlue =  average ;
            image[i][j].rgbtGreen =  average ;
            image[i][j].rgbtRed =  average ;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
     for (int i=0; i<=height-1; i++)
    {
        for(int j=0; j<=width-1; j++)
        {
            if(j < width-j-1)
            {

           buffer[i][j].rgbtBlue = image[i][j].rgbtBlue ;
           buffer[i][j].rgbtGreen = image[i][j].rgbtGreen ;
           buffer[i][j].rgbtRed = image[i][j].rgbtRed ;

           image[i][j].rgbtBlue = image[i][width-j-1].rgbtBlue ;
           image[i][j].rgbtGreen = image[i][width-j-1].rgbtGreen ;
           image[i][j].rgbtRed = image[i][width-j-1].rgbtRed ;

           image[i][width-j-1].rgbtBlue = buffer[i][j].rgbtBlue ;
           image[i][width-j-1].rgbtGreen = buffer[i][j].rgbtGreen ;
           image[i][width-j-1].rgbtRed = buffer[i][j].rgbtRed ;

            }
        }
    }
    return;
}

//Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer [height][width] ;
    int w = width ;
    int h= height ;

    // making buffer for image

    for (int s=0; s<h; s++)
    {
        for(int ss=0; ss<w; ss++)
        {
        buffer[s][ss].rgbtBlue = image[s][ss].rgbtBlue ;
        buffer[s][ss].rgbtGreen = image[s][ss].rgbtGreen ;
        buffer[s][ss].rgbtRed = image[s][ss].rgbtRed ;
        }
    }

    // solution

    for(int i=0; i<h ; i++ )
    {
        for(int j=0; j<w; j++)
        {
         float avb;
         float avg;
         float avr;
    // edge
    if(i==0 && j==0)
    {
       avb = (buffer[0][0].rgbtBlue + buffer[0][1].rgbtBlue + buffer[1][0].rgbtBlue + buffer[1][1].rgbtBlue ) / 4.0 ;
       avg = ( buffer[0][0].rgbtGreen + buffer[0][1].rgbtGreen + buffer[1][0].rgbtGreen + buffer[1][1].rgbtGreen ) / 4.0 ;
       avr = (buffer[0][0].rgbtRed + buffer[0][1].rgbtRed + buffer[1][0].rgbtRed + buffer[1][1].rgbtRed ) / 4.0 ;

       image[0][0].rgbtBlue =round(avb) ;
       image[0][0].rgbtGreen = round(avg) ;
       image[0][0].rgbtRed = round(avr) ;
    }
   else if(i==0 && j==w-1)
    {
       avb = (buffer[0][w-1].rgbtBlue + buffer[0][w-2].rgbtBlue + buffer[1][w-1].rgbtBlue + buffer[1][w-2].rgbtBlue ) / 4.0 ;
       avg = ( buffer[0][w-1].rgbtGreen + buffer[0][w-2].rgbtGreen + buffer[1][w-1].rgbtGreen + buffer[1][w-2].rgbtGreen ) / 4.0 ;
       avr = (buffer[0][w-1].rgbtRed + buffer[0][w-2].rgbtRed + buffer[1][w-1].rgbtRed + buffer[1][w-2].rgbtRed ) / 4.0 ;

       image[0][w-1].rgbtBlue =round(avb) ;
       image[0][w-1].rgbtGreen = round(avg) ;
       image[0][w-1].rgbtRed = round(avr) ;
    }
    else if(i==h-1 && j==0)
    {
       avb = (buffer[h-1][0].rgbtBlue + buffer[h-1][1].rgbtBlue + buffer[h-2][0].rgbtBlue + buffer[h-2][1].rgbtBlue ) / 4.0 ;
       avg = ( buffer[h-1][0].rgbtGreen + buffer[h-1][1].rgbtGreen + buffer[h-2][0].rgbtGreen + buffer[h-2][1].rgbtGreen ) / 4.0 ;
       avr = (buffer[h-1][0].rgbtRed + buffer[h-1][1].rgbtRed + buffer[h-2][0].rgbtRed + buffer[h-2][1].rgbtRed ) / 4.0 ;

       image[h-1][0].rgbtBlue =round(avb) ;
       image[h-1][0].rgbtGreen = round(avg) ;
       image[h-1][0].rgbtRed = round(avr) ;
    }
    else if(i==h-1 && j==w-1)
    {
       avb = (buffer[h-1][w-1].rgbtBlue + buffer[h-1][w-2].rgbtBlue + buffer[h-2][w-1].rgbtBlue + buffer[h-2][w-2].rgbtBlue ) / 4.0 ;
       avg = ( buffer[h-1][w-1].rgbtGreen + buffer[h-1][w-2].rgbtGreen + buffer[h-2][w-1].rgbtGreen + buffer[h-2][w-2].rgbtGreen ) / 4.0 ;
       avr = (buffer[h-1][w-1].rgbtRed + buffer[h-1][w-2].rgbtRed + buffer[h-2][w-1].rgbtRed + buffer[h-2][w-2].rgbtRed ) / 4.0 ;

       image[h-1][w-1].rgbtBlue =round(avb) ;
       image[h-1][w-1].rgbtGreen = round(avg) ;
       image[h-1][w-1].rgbtRed = round(avr) ;
    }

    // rows 0 or height-1
    else if(i==0)
    {
       avb = (buffer[0][j].rgbtBlue + buffer[0][j-1].rgbtBlue + buffer[0][j+1].rgbtBlue + buffer[1][j].rgbtBlue +  buffer[1][j-1].rgbtBlue + buffer[1][j+1].rgbtBlue  ) / 6.0 ;
       avg = (buffer[0][j].rgbtGreen + buffer[0][j-1].rgbtGreen + buffer[0][j+1].rgbtGreen + buffer[1][j].rgbtGreen +  buffer[1][j-1].rgbtGreen + buffer[1][j+1].rgbtGreen  ) / 6.0 ;
       avr = (buffer[0][j].rgbtRed + buffer[0][j-1].rgbtRed + buffer[0][j+1].rgbtRed + buffer[1][j].rgbtRed +  buffer[1][j-1].rgbtRed + buffer[1][j+1].rgbtRed  ) / 6.0 ;

       image[0][j].rgbtBlue =round(avb) ;
       image[0][j].rgbtGreen = round(avg) ;
       image[0][j].rgbtRed = round(avr) ;
    }
    else if(i==h-1)
    {
       avb = (buffer[h-1][j].rgbtBlue + buffer[h-1][j-1].rgbtBlue + buffer[h-1][j+1].rgbtBlue + buffer[h-2][j].rgbtBlue +  buffer[h-2][j-1].rgbtBlue + buffer[h-2][j+1].rgbtBlue  ) / 6.0 ;
       avg = (buffer[h-1][j].rgbtGreen + buffer[h-1][j-1].rgbtGreen + buffer[h-1][j+1].rgbtGreen + buffer[h-2][j].rgbtGreen +  buffer[h-2][j-1].rgbtGreen + buffer[h-2][j+1].rgbtGreen  ) / 6.0 ;
       avr = (buffer[h-1][j].rgbtRed + buffer[h-1][j-1].rgbtRed + buffer[h-1][j+1].rgbtRed + buffer[h-2][j].rgbtRed +  buffer[h-2][j-1].rgbtRed + buffer[h-2][j+1].rgbtRed  ) / 6.0 ;

       image[h-1][j].rgbtBlue =round(avb) ;
       image[h-1][j].rgbtGreen = round(avg) ;
       image[h-1][j].rgbtRed = round(avr) ;
    }
    // coloumns 0 or weidth-1
    else if(j==0)
    {
       avb = (buffer[i][0].rgbtBlue + buffer[i-1][0].rgbtBlue + buffer[i+1][0].rgbtBlue + buffer[i][1].rgbtBlue +  buffer[i-1][1].rgbtBlue + buffer[i+1][1].rgbtBlue  ) / 6.0 ;
       avg = (buffer[i][0].rgbtGreen + buffer[i-1][0].rgbtGreen + buffer[i+1][0].rgbtGreen + buffer[i][1].rgbtGreen +  buffer[i-1][1].rgbtGreen + buffer[i+1][1].rgbtGreen  ) / 6.0 ;
       avr = (buffer[i][0].rgbtRed + buffer[i-1][0].rgbtRed  + buffer[i+1][0].rgbtRed  + buffer[i][1].rgbtRed  +  buffer[i-1][1].rgbtRed  + buffer[i+1][1].rgbtRed   ) / 6.0 ;

       image[i][0].rgbtBlue =round(avb) ;
       image[i][0].rgbtGreen = round(avg) ;
       image[i][0].rgbtRed = round(avr) ;
    }
    else if(j==w-1)
    {
       avb = (buffer[i][w-1].rgbtBlue + buffer[i-1][w-1].rgbtBlue + buffer[i+1][w-1].rgbtBlue + buffer[i][w-2].rgbtBlue +  buffer[i-1][w-2].rgbtBlue + buffer[i+1][w-2].rgbtBlue  ) / 6.0 ;
       avg = (buffer[i][w-1].rgbtGreen + buffer[i-1][w-1].rgbtGreen + buffer[i+1][w-1].rgbtGreen + buffer[i][w-2].rgbtGreen +  buffer[i-1][w-2].rgbtGreen + buffer[i+1][w-2].rgbtGreen  ) / 6.0 ;
       avr = (buffer[i][w-1].rgbtRed + buffer[i-1][w-1].rgbtRed + buffer[i+1][w-1].rgbtRed + buffer[i][w-2].rgbtRed +  buffer[i-1][w-2].rgbtRed + buffer[i+1][w-2].rgbtRed  ) / 6.0 ;

       image[i][w-1].rgbtBlue =round(avb) ;
       image[i][w-1].rgbtGreen = round(avg) ;
       image[i][w-1].rgbtRed = round(avr) ;
    }
    // not 1 or 2 or 3
    else
    {
    float sumg =0.0 ;
    float sumr =0.0 ;
    float sumb =0.0 ;
    for(int m=0;m<3;m++)
    {
        for(int mm=0;mm<3;mm++)
        {
        sumb = sumb+ buffer[i-m+1][j-mm+1].rgbtBlue ;
        sumg = sumg+ buffer[i-m+1][j-mm+1].rgbtGreen ;
        sumr = sumr+ buffer[i-m+1][j-mm+1].rgbtRed ;
        }
    }
     image[i][j].rgbtBlue=round(sumb/9.0);
     image[i][j].rgbtGreen=round(sumg/9.0);
     image[i][j].rgbtRed=round(sumr/9.0);

    }

        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
       RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;

            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
                    gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];
                    gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
                    gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                }
            }

            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
