#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main()
{
    float a[10][10],b[10],y[11],x[11], max,phi, T=0;
    float h=0.1;
    for(int i=0; i<11; i++)
    {
        y[i] = T;
        T= T + 0.1;
    }
    cout<<"Enter the value of phi:"<<endl;
    cin>>phi;
    int i = 0;
    a[i][0] = -2-(phi*phi*h*h);
    a[i][1] = 2;
    for(int j = 2; j<10; j++)
    {
        a[i][j]=0;
    }
    for(int i=1; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(j==(i-1) ||j==(i+1))
                a[i][j]=1;
            else if(i==j)
                a[i][j]=-2-phi*phi*h*h;
            else
            {
                a[i][j]=0;
            }
        }
    }

    for (int j = 0; j<9; j++)
    {
        b[j]=0;
    }
    b[9] = -1;
    float alpha,beta;
    int r = 10;
    for (int i =0 ; i<r; i++)
    {
        for (int j = 1; j<(r-i); j++)
        {
            if(a[i][i]==0)
            {
                max =a[i][i];
                for (int w =i ; w<r; w++)
                {
                    if (a[i+w][i]>max)
                    {
                        max = a[i+w][i];
                    }
                }
                for (int w =i ; w<r; w++)
                {
                    if(a[i+w][i]==max)
                    {
                        for (int w = 0; w<10; w++)
                        {
                            float temp1 = a[i+w][w];
                            a[i+w][w]=a[i][w];
                            a[i][w] = temp1;
                        }
                        float temp2 = b[i+w];
                        b[i+w]=b[i];
                        b[i] = temp2;
                    }
                }


            }
            alpha = a[i][i];
            beta =a[i+j][i];
            for (int z =0 ; z<r; z++ )
            {
                a[i+j][z] = (alpha*a[i+j][z]-beta*a[i][z])/alpha;

            }
            b[i+j] = (alpha*b[i+j]-beta*b[i])/alpha;

        }

    }


    /*for(int i = 0;i<10;i++)
    {for(int j= 0;j<10;j++)
    {cout<<a[i][j]<<" ";
    }cout<<endl;
    }*/

    x[10]=1;
    float sum=0;
    int p;
    x[9]=b[9]/a[9][9];

    for(int l=9; l>=0; l--)
    {
        x[l]=b[l];
        for(int i=9; i>l; i--)
        {
            x[l]=x[l]-(a[l][i]*x[i]);
        }
        x[l]=x[l]/a[l][l];

    }


    ofstream outfile;
    outfile.open("xy20.dat",ios::out);
    x[10] =1;
    for(int j=0; j<11; j++)
    {
        outfile<<y[j]<<" "<<x[j]<<endl;
    }

    ofstream outfile1;
    outfile1.open("y1.dat",ios::out);
    for(int j=0; j<=10; j++)
    {
        outfile1<<y[j]<<" "<<(cosh(phi*x[j]))/cosh(phi)<<endl;
    }

    for(int i=1; i<10; i+=2)
    {
        sum=sum+(h/3)*(x[i-1]+4*x[i]+x[i+1]);
    }
    cout<<"The value of the integration is :"<<sum<<endl;
    cout<<"The analxtical value of eta is :"<<tanh(phi)/(phi)<<endl;

}
