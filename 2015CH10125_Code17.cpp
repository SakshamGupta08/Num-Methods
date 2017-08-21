#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

void derivative(float k,float R,float S,float y[3],float f[3])
{
    f[0]=k*R*(1-y[0])*(1-y[1])+(S-R)*(1-y[1])*y[2];
    f[1]=k*(1-y[0])*(1-y[1]);
    f[2]=(y[0]-1)*y[2];
}

float sum(float error[3])
{
    float s=0;
    for(int k=0; k<3; k++)
    {
        s=s+error[k];
    }
    s=pow(s,0.5);
    return s;
}

int main()
{

    float h=1;
    float error[3];
    error[0]=error[1]=error[2]=1;
    float y[3];
    float tol=0.001;
    float y_init[3];
    float k=2;
    float R=0.33;
    float S=0.33;
    float k1[3],k2[3],k3[3],k4[3];
    float total_error=1;


    while(total_error>abs(tol))
    {

        ofstream outfile1;
        ofstream outfile2;
        ofstream outfile3;
        outfile1.open("y1.txt",ios::out);
        outfile2.open("y2.txt",ios::out);
        outfile3.open("y3.txt",ios::out);
        y[0]=0;
        y[1]=0;
        y[2]=1;


        for(int j=0; j<(5/h); j++)
        {
            for(int i=0; i<3; i++)
            {
                y_init[i]=y[i];
            }
            derivative(2,0.33,0.33,y,k1);

            for(int i=0; i<3; i++)
            {
                y[i]=y_init[i]+(h/2)*k1[i];
            }
            derivative(2,0.33,0.33,y,k2);
            for(int i=0; i<3; i++)
            {
                y[i]=y_init[i]+(h/2)*k2[i];
            }

            derivative(2,0.33,0.33,y,k3);
            for(int i=0; i<3; i++)
            {
                y[i]=y_init[i]+((h)*k3[i]);
            }
            derivative(2,0.33,0.33,y,k4);
            for(int i=0; i<3; i++)
            {
                y[i]=y_init[i]+((h/6)*(k1[i]+2*k2[i]+2*k3[i]+k4[i]));
                error[i]=pow((y[i]-y_init[i]),2);
            }

            outfile1<<(j*h)+h<<" "<<y[0]<<endl;
            outfile2<<(j*h)+h<<" "<<y[1]<<endl;
            outfile3<<(j*h)+h<<" "<<y[2]<<endl;
            total_error=sum(error);
        }

        h=h/2;
    }
}



