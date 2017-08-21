#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main()
{
    ifstream myfile;
    myfile.open("input_selfmade1.dat",ios::in);
    int a,b;
    myfile>>a>>b;
    float A[a][b];
    for (int i=0; i<a; i++)
    {
        for (int j=0; j<b; j++)
        {
            myfile>>A[i][j];

        }
    }
    myfile.clear();
    myfile.close();


    myfile.open("input_selfmade2.dat",ios::in);
    int m,n;
    myfile>>m>>n;
    float B[m][n] ;
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
        {
            myfile>>B[i][j];

        }
    }
    myfile.clear();
    myfile.close();

    if(a!=b)
    {
        cout<<"Not possible through Gaussian method"<<endl;
        return 0;
    }

    cout<<"Matrix A is: "<<endl;

    for (int i=0; i<a; i++)
    {
        cout<<endl;
        for(int j=0; j<b; j++)
        {
            cout<<A[i][j]<<" ";
        }
    }
    cout<<endl;

    cout<<"Matrix B is: "<<endl;

    for (int i=0; i<m; i++)
    {
        cout<<endl;
        for(int j=0; j<n; j++)
        {
            cout<<B[i][j]<<" ";
        }
    }
    cout<<endl;

    float I[a][b];
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
        {
            if(i==j)I[i][j]=1;
            else I[i][j]=0;
        }
    }

    cout<<"Identity matrix is :"<<endl;
    for (int i=0; i<a; i++)
    {
        cout<<endl;
        for(int j=0; j<b; j++)
        {
            cout<<I[i][j]<<" ";
        }
    }
    cout<<endl;




    int k=0;
    while(k<b)
    {
        float d=A[k][k];

        B[k][n-1]=B[k][n-1]/d;
        for(int i=0; i<b; i++)
        {
            A[k][i]=A[k][i]/d;
            I[k][i]=I[k][i]/d;


        }
        for(int i=0; i<a; i++)
        {
            if(i!=k)
            {
                double c= A[i][k]/A[k][k];
                B[i][n-1]=B[i][n-1] - (c)*B[k][n-1];
                if (abs(B[i][n-1])<pow(10,-8)) B[i][n-1]=0;

                for(int j=0; j<b; j++)
                {
                    A[i][j]=A[i][j]- (c)*A[k][j];
                    I[i][j]=I[i][j]- (c)*I[k][j];

                    if (abs(A[i][j])<pow(10,-8)) A[i][j]=0;
                    if (abs(I[i][j])<pow(10,-8)) I[i][j]=0;
                }
            }
        }

        k=k+1;
    }

    cout<<"Solution set is: "<<endl;
    for (int i=0; i<m; i++)
    {
        cout<<endl;
        for(int j=0; j<n; j++)
        {
            cout<<B[i][j]<<" ";
        }
    }
    cout<<endl;

    cout<<"Inverse is: " <<endl;
    for (int i=0; i<a; i++)
    {
        cout<<endl;
        for(int j=0; j<b; j++)
        {
            cout<<I[i][j]<<" ";
        }
    }

    cout<<endl;
}




