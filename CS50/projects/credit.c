#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    // VISA 16 MASTERCARD code
    long c ;
    c= get_long("Card number:");

    long y ;
    long sum1=0;
    for(int i=0;i<=14;i=i+2)
    {
         long x = pow(10,i);
         y= 2*(c%(100*x)-c%(10*x))/(10*x);
         if (y>9)
         {
             int m = y%10;
             int n = (y%100-y%10)/10;
             int z =m+n;
             y=z;
         }
         sum1=sum1+y;
    }

     long sum2=0;
     long b;

     for(int j=0;j<=14;j=j+2)
    {
         long t = pow(10,j);
         b=(c%(10*t)-c%(1*t))/(1*t);
         sum2=sum2+b;
    }

     int sum3=sum1+sum2;
     long g = pow(10,16); long k= pow(10,15);
     long h = pow(10,15); long v= pow(10,14);
     long G = (c%g-c%k)/k;
     long H = (c%h-c%v)/v;

     // VISA 13 CODE

    long yy ;
    long sum11=0;
    for(int ii=0;ii<=10;ii=ii+2)
    {
         long xx = pow(10,ii);
         yy= 2*(c%(100*xx)-c%(10*xx))/(10*xx);
         if (yy>9)
         {
             int mm = yy%10;
             int nn = (yy%100-yy%10)/10;
             int zz =mm+nn;
             yy=zz;
         }
         sum11=sum11+yy;
    }

     long sum22=0;
     long bb;

     for(int jj=0;jj<=12;jj=jj+2)
    {
         long tt = pow(10,jj);
         bb=(c%(10*tt)-c%(1*tt))/(1*tt);
         sum22=sum22+bb;
    }

     int sum33=sum11+sum22;
     long gg = pow(10,13); long kk= pow(10,12);
     long GG = (c%gg-c%kk)/kk;

     // AMEX 15 CODE
    long yyy ;
    long sum111=0;
    for(int iii=0;iii<=12;iii=iii+2)
    {
         long xxx = pow(10,iii);
         yyy= 2*(c%(100*xxx)-c%(10*xxx))/(10*xxx);
         if (yyy>9)
         {
             int mmm = yyy%10;
             int nnn = (yyy%100-yyy%10)/10;
             int zzz =mmm+nnn;
             yyy=zzz;
         }
         sum111=sum111+yyy;
    }

     long sum222=0;
     long bbb;

     for(int jjj=0;jjj<=14;jjj=jjj+2)
    {
         long ttt = pow(10,jjj);
         bbb=(c%(10*ttt)-c%(1*ttt))/(1*ttt);
         sum222=sum222+bbb;
    }

     int sum333=sum111+sum222;
     long ggg = pow(10,15); long kkk= pow(10,14);
     long hhh = pow(10,14); long vvv= pow(10,13);
     long GGG = (c%ggg-c%kkk)/kkk;
     long HHH = (c%hhh-c%vvv)/vvv;
     // checking if the CARD is valid
    if (c<=999999999999)
    {
       printf("INVALID\n");
    }
    else if (c>999999999999 && c<=9999999999999 && sum33%10==0 && GG==4)
    {
          printf("VISA\n");
    }
    else if (c>99999999999999 && c<=999999999999999 && sum333%10==0 && GGG==3 && (HHH==4 || HHH==7))
    {
         printf("AMEX\n");
    }
    else if (c>999999999999999 && c<=9999999999999999 && G==4 && sum3%10==0 )
    {
         printf("VISA\n");
    }
    else if(c>999999999999999 && c<=9999999999999999 && G==5 && (H==1|| H==2||H==3 || H==4 || H==5) && sum3%10==0)
    {
         printf("MASTERCARD\n");
    }
    else
    {
          printf("INVALID\n");
    }
}