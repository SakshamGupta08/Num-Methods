#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main()
{
    float C[11]= {1.79*pow(10,-4),2.03*pow(10,-4),2.22*pow(10,-4),2.47*pow(10,-4),2.97*pow(10,-4),3.39*pow(10,-4),4.95*pow(10,-4),7.37*pow(10,-4),9.01*pow(10,-4),9.83*pow(10,-4),10.07*pow(10,-4)};
    float r[11]= {0.28*pow(10,-2),0.32*pow(10,-2),0.36*pow(10,-2),0.40*pow(10,-2),0.49*pow(10,-2),0.59*pow(10,-2),0.99*pow(10,-2),1.55*pow(10,-2),2.00*pow(10,-2),2.25*pow(10,-2),2.60*pow(10,-2)};
    float sum_x=0;
    for (int i=0; i<11; i++)
    {
        sum_x=sum_x+log(C[i]);
    }
    float sq_sum=0;
    for (int i=0; i<11; i++)
    {
        sq_sum=sq_sum+(log(C[i])*log(C[i]));
    }
    float sum_y=0;
    for (int i=0; i<11; i++)
    {
        sum_y=sum_y+log(r[i]);
    }
    float sum=0;
    for (int i=0; i<11; i++)
    {
        sum=sum+(log(r[i])*log(C[i]));
    }
    float A[2][2]= {{11,sum_x},{sum_x,sq_sum}};
    float B[2]= {sum_y,sum};

    int k=0;
    while(k<2)
    {
        float d=A[k][k];

        B[k]=B[k]/d;
        for(int i=0; i<2; i++)
        {
            A[k][i]=A[k][i]/d;


        }
        for(int i=0; i<2; i++)
        {
            if(i!=k)
            {
                double c= A[i][k]/A[k][k];
                B[i]=B[i] - (c)*B[k];
                if (abs(B[i])<pow(10,-8)) B[i]=0;

                for(int j=0; j<2; j++)
                {
                    A[i][j]=A[i][j]- (c)*A[k][j];

                    if (abs(A[i][j])<pow(10,-8)) A[i][j]=0;
                }
            }
        }

        k=k+1;
    }
   cout<<"The order of the reaction is : "<<B[1]<<endl;
   float K= pow(2.71828,B[0]);
    ofstream outfile;
    outfile.open("xy20.txt");
    for(float x=C[0]; x<=C[10]; x=x+0.00001)
    {
        outfile<<x<<" "<<K*pow(x,B[1])<<endl;
    }
}








