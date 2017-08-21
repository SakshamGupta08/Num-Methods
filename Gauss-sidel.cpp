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

    for(int k=0;k<a;k++){
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
            float temp = A[k][r];
            A[k][r] = A[index][r];
            A[index][r] = temp;
        }
        for(int r=0; r<n; r++)
        {
            float temp2=B[k][r];
            B[k][r]=B[index][r];
            B[index][r]=temp2;
        }
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


int i,j,k;

    cout<<"Enter our initial assumption set: "<<endl;

    float X[m],Y[m];
    for(j=0; j<m; j++)
    {
        cin>>X[j];
    }
    for(j=0; j<m; j++)
    {
        Y[j]=0;
    }
    float e=10,error;

    cout<<"Error allowed : "<<endl;
    cin>>error;

    float E[m];
    /*int count=0;

    cout<<"Enter max number of iterations:"<<endl;
    cin>>count;*/

    while(e>=error)
    {
        for(i=0; i<m; i++)
        {
            Y[i]=X[i];
            float sum=0;
            for(k=0; k<a; k++)
            {
                if(k!=i)
                {
                    sum=sum+(A[i][k]*X[k]);
                }
            }
            X[i]=(B[i][n-1]-sum)/A[i][i];
            E[i]=X[i]-Y[i];
        }
        e=abs(E[0]);
        for(i=0; i<m; i++)
        {
            if(abs(E[i])>=e) e=E[i];
        }
        for(i=0; i<m; i++)
        cout<<X[i]<<endl;
    cout<<endl;

    }

    /*cout<<endl<<"Set of solution is"<<endl;
    for(i=0; i<m; i++)
        cout<<X[i]<<endl;
    cout<<endl;*/



}

