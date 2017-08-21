#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
using namespace std;


float func(int choice,int i,int j,int k,float initial[2])
{
    float var[2];
    float Fx;
    for(int i=0; i<2; i++)
    {
        var[i]=initial[i];
    }

    float Delta=0.00001;

    if(k==1)
    {
        var[j] = var[j] + Delta;

    }

    if(i==0)
    {
        if(choice==1)
            Fx = 8*var[1] + 2*var[0]*var[1] -62 -39*var[0] -8*var[0]*var[0] - pow(var[0],3);
        if(choice==2)
            Fx = -6.25 -0.5*var[0] -var[0]*var[0] -pow(var[0],3) +2*var[0]*var[1] +var[1];
    }

    if(i==1)
    {
        if(choice==1)
            Fx = 50 -39*var[1] +var[1]*var[1] -8*var[0]*var[1] - var[0]*var[0]*var[1];
        if(choice==2)
            Fx = 39.0625 -0.5*var[1] -var[0]*var[1] -var[0]*var[0]*var[1] +var[1]*var[1];
    }
    return Fx;
}


void FindInv(float A[2][2],int n)
{
    float I[5][5];
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

}

void findroots(float a,float b,float c)
{
    float root[2][2];
    float D=b*b-4*a*c;
    if(D>=0)
    {
        root[0][0] = (-b + pow(D,0.5))/(2*a);
        root[1][0] = (-b - pow(D,0.5))/(2*a);
        root[0][1]=root[1][1]=0;
    }
    else
    {
        root[0][0]=root[1][0]= -b/(2*a);
        root[0][1]=pow(abs(D),0.5)/(2*a);
        root[1][1]=-pow(abs(D),0.5)/(2*a);
    }

    cout<<"roots of equation are: "<<endl;
    cout<<root[0][0]<<" + "<<root[0][1]<<"i"<<endl;
    cout<<root[1][0]<<" + "<<root[1][1]<<"i"<<endl;
}

int main()
{
    float Fx[2];
    float initial[2];

    float Delta=0.00001;
    float Jacob[2][2];
    float Tolerance;
    int choice;
    cout<<"Which case do you want to run? (1 or 2)"<<endl;
    cin>>choice;

    initial[0] = 1;
    initial[1] = 1;

    if(choice==1)
    {
        Fx[0] = 8*initial[1] + 2*initial[0]*initial[1] -62 -39*initial[0] -8*initial[0]*initial[0] - pow(initial[0],3);
        Fx[1] = 50 -39*initial[1] +initial[1]*initial[1] -8*initial[0]*initial[1] - initial[0]*initial[0]*initial[1];
    }

    if(choice==2)
    {
        Fx[0] = -6.25 -0.5*initial[0] -initial[0]*initial[0] -pow(initial[0],3) +2*initial[0]*initial[1] +initial[1];
        Fx[1] = 39.0625 -0.5*initial[1] -initial[0]*initial[1] -initial[0]*initial[0]*initial[1] +initial[1]*initial[1];
    }
    do
    {

        Tolerance = 0;
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<2; j++)
            {

                Jacob[i][j] = (func(choice,i,j,1,initial) - func(choice,i,j,0,initial))/Delta;

            }
        }

        FindInv(Jacob,2);
        if(choice==1)
        {
            Fx[0] = 8*initial[1] + 2*initial[0]*initial[1] -62 -39*initial[0] -8*initial[0]*initial[0] - pow(initial[0],3);
            Fx[1] = 50 -39*initial[1] +initial[1]*initial[1] -8*initial[0]*initial[1] - initial[0]*initial[0]*initial[1];
        }
        if(choice==2)
        {
            Fx[0] = -6.25 -0.5*initial[0] -initial[0]*initial[0] -pow(initial[0],3) +2*initial[0]*initial[1] +initial[1];
            Fx[1] = 39.0625 -0.5*initial[1] -initial[0]*initial[1] -initial[0]*initial[0]*initial[1] +initial[1]*initial[1];
        }
        float sum =0, multiply[2];
        for(int a=0; a<2; a++)
        {
            for(int b=0; b<2; b++)
            {
                sum = sum + Jacob[a][b]*Fx[b];
            }
            multiply[a] = sum ;
            sum =0;
        }


        for(int a=0; a<2; a++)
        {
            initial[a] = initial[a] - multiply[a];
            Tolerance += pow(multiply[a],2);
        }

        Tolerance = pow(Tolerance,0.5);
    }
    while(Tolerance>0.00001);
    float p=initial[0];
    float q=initial[1];

    cout<<"The value of p is :"<<p<<endl;
    cout<<"The value of q is :"<<q<<endl;

    if(choice==1)
    {
        findroots(1,p,q);
        findroots(1,-8-p,39-q+(p*p)+(8*p));
    }

    if(choice==2)
    {
        findroots(1,p,q);
        findroots(1,-1-p,0.5-p*(-1-p)-q);
    }
}


