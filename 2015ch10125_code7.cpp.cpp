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
            cout<<A[i][j]<<"\t";
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

    float U[100][100],L[100][100];
    int i,j,k;
    float sum;
    for(j=0; j<b; j++)
    {
        U[0][j] = A[0][j];

    }

    for(i=0; i<a; i++)
    {
        L[i][0] = A[i][0] / U[0][0];

    }

    for(i=1; i<a; i++)
    {
        L[i][i] = 1;
        for(j=i; j<b; j++)
        {
            sum = 0;
            for(k=0; k<i; k++)
            {
                sum=sum+(L[i][k] * U[k][j]);
            }
            U[i][j] = (A[i][j] - sum);


        }
        for(j=i+1; j<a; j++)
        {
            sum =0;
            for(k=0; k<i; k++)
            {
                sum=sum+(L[j][k]*U[k][i]);
            }
            L[j][i] = (A[j][i]- sum)/U[i][i];

        }
    }

    cout<<endl<<"L matrix is "<<endl;
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
            cout<<L[i][j]<<"  ";
        cout<<endl;
    }
    cout<<endl;
    cout<<endl<<"U matrix is "<<endl;
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
            cout<<U[i][j]<<"  ";
        cout<<endl;
    }

    float Y[a],X[a];
    Y[0]=B[0][0]/L[0][0];
    for(int i=1; i<a; i++)
    {
        float sum=0;
        for(int p=0; p<i; p++)
        {
            sum=sum+(L[i][p]*Y[p]);
        }
        if(L[i][i]==0)
        {
            cout<<"Can't do further"<<endl;
            return 0;
        }
        else
        {
            Y[i]=(B[i][n-1]-sum)/L[i][i];
        }
    }

    X[a-1]=Y[a-1]/U[a-1][a-1];
    for(int i=a-2; i>=0; i--)
    {
        float sum=0;
        for(int p=i+1; p<a; p++)
            sum=sum+(U[i][p]*X[p]);
        if(U[i][i]==0)
        {
            cout<<"Cannot do further"<<endl;
            return 0;
        }
        else
        {
            X[i]=(Y[i]-sum)/U[i][i];
        }
    }


    cout<<endl<<"Y vector is"<<endl;
    for(int i=0; i<a; i++)
        cout<<endl<<Y[i];
    cout<<endl;

    cout<<endl<<"Set of solution is"<<endl;
    for(int i=0; i<a; i++)
        cout<<endl<<X[i];
    cout<<endl;


}








