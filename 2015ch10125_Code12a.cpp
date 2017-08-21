#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
using namespace std;

float func(int i,int j,int k,float C_init[4])
{
    float k1=1,k2=0.2,k3=0.05,k4=0.4;
    float Q=2;
    float Cao=1;
    float Fx;
    float C_t[5];

    for(int p=0; p<4; p++)
    {
        C_t[p] = C_init[p];
    }
    float Delta=0.00001;

    if(k==1)
    {
        C_t[j] = C_t[j] + Delta;
    }

    if(i==0)
    {
        Fx = -C_t[0] + Cao +(-k1*C_t[0] - k2*pow(C_t[0],1.5) + k3*pow(C_t[2],2))*Q;
    }

    if(i==1)
    {
        Fx = -C_t[1] + (2*k1*C_t[0] - k4*C_t[1]*C_t[1])*Q;
    }
    if(i==2)
    {
        Fx = -C_t[2] + (k2*pow(C_t[0],1.5) - k3*pow(C_t[2],2) + k4*C_t[1]*C_t[1])*Q;
    }
    if(i==3)
    {
        Fx = -C_t[3] + k4*C_t[1]*C_t[1]*Q;
    }

    return Fx;
}



void FindInv(float A[4][4],int n)
{
    float I[100][100];
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==j) I[i][j]=1;
            else I[i][j]=0;
        }
    }

    int k=0;
    while(k<n)
    {
        float d=A[k][k];

        for(int i=0; i<n; i++)
        {
            A[k][i]=A[k][i]/d;
            I[k][i]=I[k][i]/d;

        }
        for(int i=0; i<n; i++)
        {
            if(i!=k)
            {
                double c= A[i][k]/A[k][k];
                for(int j=0; j<n; j++)
                {
                    A[i][j]=A[i][j]- (c)*A[k][j];
                    I[i][j]=I[i][j]- (c)*I[k][j];

                    if (abs(A[i][j])<pow(10,-8)) A[i][j]=0;
                    if (abs(I[i][j])<pow(10,-5)) I[i][j]=0;
                }
            }
        }

        k=k+1;
    }

    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            A[i][j]=I[i][j];
        }
    }

    /*cout<<"Inverse is: " <<endl;
    for (int i=0; i<n; i++)
    {
        cout<<endl;
        for(int j=0; j<n; j++)
        {
            cout<<A[i][j]<<" ";
        }
    }*/
}


int main()
{
    float Fx[4];
    float C[4];
    float Cao =1;

    float k1=1,k2=0.2,k3=0.05,k4=0.4;
    float Q=2;

    float DelC=0.00001;
    float Jacob[4][4];
    float Tolerance;

    C[0] = 1;
    C[1] = 1;
    C[2] = 1;
    C[3] = 1;


    Fx[0] = -C[0] + Cao +(-k1*C[0] - k2*pow(C[0],1.5) + k3*pow(C[2],2))*Q;
    Fx[1] = -C[1] + (2*k1*C[0] - k4*C[1]*C[1])*Q;
    Fx[2] = -C[2] + (k2*pow(C[0],1.5) - k3*pow(C[2],2) + k4*C[1]*C[1])*Q;
    Fx[3] = -C[3] + k4*C[1]*C[1]*Q;

    do
    {

        Tolerance = 0;
        // Finding Jacobian
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {

                Jacob[i][j] = (func(i,j,1,C) - func(i,j,0,C))/DelC;

            }
        }

        FindInv(Jacob,4);

        Fx[0] = -C[0] + Cao +(-k1*C[0] - k2*pow(C[0],1.5) + k3*pow(C[2],2))*Q;
        Fx[1] = -C[1] + (2*k1*C[0] - k4*C[1]*C[1])*Q;
        Fx[2] = -C[2] + (k2*pow(C[0],1.5) - k3*pow(C[2],2) + k4*C[1]*C[1])*Q;
        Fx[3] = -C[3] + k4*C[1]*C[1]*Q;

        float sum =0, multiply[4];
        for(int a=0; a<4; a++)
        {
            for(int b=0; b<4; b++)
            {
                sum = sum + Jacob[a][b]*Fx[b];
            }
            multiply[a] = sum ;
            sum =0;
        }


        for(int a=0; a<4; a++)
        {
            C[a] = C[a] - multiply[a];
            Tolerance += pow(multiply[a],2);
        }

        Tolerance = pow(Tolerance,0.5);

    }
    while(Tolerance>0.00001);

    cout<<"The Concentrations Are :"<<endl;
    for(int i=0; i<4; i++)
    {
        cout<<C[i]<<endl;
    }

}

