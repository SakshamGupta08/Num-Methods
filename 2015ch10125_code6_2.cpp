#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main()
{
    ifstream myfile1;
    ifstream myfile2;
    myfile1.open("input2_10x10.dat",ios::in);
    myfile2.open("input2_10x1.dat",ios::in);
    int a,b,m,n;
    int i=0;
    int j=0;
    myfile1>>a>>b;
    myfile2>>m>>n;
    float A[(2*a)+m][(2*b)+n];
    for (int i=0; i<a; i++)
    {
        for (int j=0; j<b; j++)
        {
            myfile1>>A[i][j];

        }


        for (int j=b; j<b+n; j++)
        {
            myfile2>>A[i][j];

        }
    }
    myfile1.close();
    myfile2.close();


    if(a!=b)
    {
        cout<<"Not possible through Gauss-Jordan method"<<endl;
        return 0;
    }

    for (int i=0; i<a; i++)
    {
        for(int j=b+n; j<(2*b)+n; j++)
        {
            if((i+b+n)==j)A[i][j]=1;
            else A[i][j]=0;
        }
    }


    for (int i=0; i<a; i++)
    {
        cout<<endl;
        for(int j=0; j<(2*b)+n; j++)
        {
            cout<<A[i][j]<<" ";
        }
    }
    cout<<endl;



    int k=0;
    float temp1;
    while(k<b)
    {
        int index=k;
        int l;
        float max=A[k][k];
        for(l=k; l<a; l++)
        {
            if(max<abs(A[l][k]))
            {
                max= A[l][k];
                index = l;
            }
        }

        for(int r=0; r<(b+n+b) ; r++)
        {
            temp1 = A[k][r];
            A[k][r] = A[index][r];
            A[index][r] = temp1;
        }

        for(int i=k+1; i<a; i++)
        {
            double c= A[i][k]/A[k][k];
            for(int j=k; j<(b+n+b); j++)
            {
                A[i][j]=A[i][j]- (c)*A[k][j];

                if (abs(A[i][j])<pow(10,-8)) A[i][j]=0;

            }
        }
        k=k+1;
    }
    for(int k=0; k<a; k++)
    {
        float d=A[k][k];
        for(int i=0; i<(b+n+b); i++)
        {
            A[k][i]=A[k][i]/d;

        }
    }
    for(int k=1; k<a; k++)
    {
        for(int i=0; i<k; i++)
        {
            double c= A[i][k]/A[k][k];
            for(int j=k; j<(b+n+b); j++)
            {
                A[i][j]=A[i][j]- (c)*A[k][j];

                if (abs(A[i][j])<pow(10,-8)) A[i][j]=0;

            }

        }

    }

    cout<<endl;

    cout<<"Answer set is: "<<endl;

    for (int i=0; i<a; i++)
    {
        cout<<endl;
        for(int j=b; j<(b+n); j++)
        {
            cout<<A[i][j]<<" ";
        }
    }

    cout<<endl;
    cout<<endl;
    cout<<"Inverse is: "<<endl;

    for (int i=0; i<a; i++)
    {
        cout<<endl;
        for(int j=b+n; j<(b+n+b); j++)
        {
            cout<<A[i][j]<<" ";
        }
    }

    cout<<endl;


}




