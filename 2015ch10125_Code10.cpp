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


    float I[a][b];
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
        {
            if(i==j) I[i][j]=1;
            else I[i][j]=0;
        }
    }

    cout<<"Identity matrix is:"<<endl;
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<a; j++)
        {
            cout<<I[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    int count=1;

    int k=0;

    for(k; k<a; k++)
    {
        if(count<a-1)
        {

            float s=0;
            for(int i=k+1; i<a; i++)
            {
                s=s + (A[k][i]*A[k][i]);
            }
            float S=sqrt(s);
            cout<<"Value of S is:"<<S<<endl;

            float w[a];
            for(int i=0; i<=k; i++)
            {
                w[i]=0;
            }

            w[k+1]= pow((0.5*(1+ (abs(A[k][k+1])/S))),0.5);
            cout<<"Value of w[k+1] :"<<w[k+1]<<endl;

            for (int i=0; i<a; i++)
            {
                if(i>k+1)
                {
                    w[i]=(A[k][i]*A[k][k+1]/abs(A[k][k+1]))/(2*S*w[k+1]);
                }
            }
            cout<<endl;

            cout<<"Matrix w is :"<<endl;

            for(int i=0; i<a; i++)
            {
                cout<<w[i]<<endl;
            }
            cout<<endl;
            float B[a][a];
            cout<<"Matrix B is :"<<endl;
            for(int i=0; i<a; i++)
            {
                for(int j=0; j<a; j++)
                {
                    B[i][j]=I[i][j]-(2*w[i]*w[j]);
                    cout<<B[i][j]<<" "<<" ";
                }
                cout<<endl;
            }
            //cout<<endl;

            float C[a][a];
            for(int i=0; i<a; i++)
            {
                for(int j=0; j<a; j++)
                {
                    C[i][j]= 0;
                    for(int k=0; k<b; k++)
                    {
                        C[i][j]+=B[k][i]*A[k][j];

                    }
                    //     cout<<C[i][j]<<" ";
                }
                //cout<<endl;

            }
            cout<<endl;

            float A2[a][a];
            for(int i=0; i<a; i++)
            {
                for(int j=0; j<a; j++)
                {
                    A2[i][j]= 0;
                    for(int k=0; k<b; k++)
                    {
                        A2[i][j]+=C[i][k]*B[k][j];

                    }
                    if(abs(A2[i][j])<pow(10,-4)) A2[i][j]=0;
                    //  cout<<A2[i][j]<<" ";
                }
                //cout<<endl;

            }
            //cout<<endl<<endl;


            for(int i=0; i<a; i++)
            {
                for(int j=0; j<a; j++)
                {
                    A[i][j]=A2[i][j];
                }
            }

        }

        count++;
    }


    cout<<endl<<"THE TRIDIAGONAL MATRIX IS : "<<endl;

    for(int i=0; i<a; i++)
    {
        for(int j=0; j<a; j++)
        {
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }

}




