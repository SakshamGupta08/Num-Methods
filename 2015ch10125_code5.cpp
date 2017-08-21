#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main()
{
    ifstream myfile;
    myfile.open("input2_10x10.dat",ios::in);
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


    myfile.open("input2_10x1.dat",ios::in);
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

    float temp1,temp2;

    int k=0;
    while(k<b)
    {


        int index=k;
        int l;
        float max=A[k][k];
        for(l=k; l<b; l++)
        {
            if(max<abs(A[l][k]))
            {
                max= A[l][k];
                index = l;
            }
        }

        for(int r=0; r<b ; r++)
        {
            temp1 = A[k][r];
            A[k][r] = A[index][r];
            A[index][r] = temp1;
        }

        for(int r=0; r<n; r++)
        {
            temp2=B[k][r];
            B[k][r]=B[index][r];
            B[index][r]=temp2;
        }

        for(int i=k+1; i<a; i++)
        {
            double c= A[i][k]/A[k][k];
            B[i][n-1]=B[i][n-1] - (c)*B[k][n-1];
            if (abs(B[i][n-1])<pow(10,-8)) B[i][n-1]=0;
 cout<<"Element is :"<<B[i][n-1]<<endl;
            for(int j=k; j<b; j++)
            {
                A[i][j]=A[i][j]- (c)*A[k][j];

                if (abs(A[i][j])<pow(10,-8)) A[i][j]=0;


            }
        }

        k=k+1;
    }

    float X[b];
    X[b-1]=(B[m-1][n-1])/(A[a-1][b-1]);
    cout<<"B is : "<<B[m-1][n-1]<<endl;
    cout<<"X is : "<<X[b-1]<<endl;
cout<<"A is : "<<A[a-1][b-1]<<endl;

    for(int i=b-2; i>=0; i--)
    {

        double sum=0;
        for(int j=i+1; j<b; j++)
        {
            sum=sum+ (A[i][j]*X[j]);
        }

        X[i]=(B[i][n-1]-sum)/A[i][i];
    }
    cout<<"Answer set is: "<<endl;
    for(int i=0; i<b; i++)
    {
        cout<<X[i]<<endl;

    }
}










