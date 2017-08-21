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

    float AA[a][b];
    for (int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
        {
            AA[i][j]=A[i][j];
        }
    }


    float II[a][b];
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
        {
            if(i==j)II[i][j]=1;
            else II[i][j]=0;
        }
    }

    float I[a][b];
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
        {
            if(i==j) I[i][j]=1;
            else I[i][j]=0;
        }
    }

    cout<<"Enter your initial/assumed eigenvector : "<<endl;
    float V[a];
    for(int i=0; i<a; i++)
    {
        cin>>V[i];
    }

    float norm;
    float error;
    float W[a];
    for(int i=0; i<a; i++)
    {
        W[i]=V[i];
    }

    cout<<"Enter max permissible error: " <<endl;
    cin>>error;


    float C[a];
    float e=100;
    float f=50;

    while(abs(e-f)>=error)
    {

        f=e;

        for (int r=0; r<a; r++)
        {
            C[r]= 0;
            for(int k=0; k<a; k++)
            {
                C[r]+=A[r][k]*V[k];
            }

        }

        float d=0;
        for(int t=0; t<a; t++)
        {
            d = d + pow(C[t],2);
        }

        e= sqrt(d);

        for(int y=0; y<a; y++)
        {

            V[y]=C[y]/e;
        }
        //cout<<"Error is: "<<abs(e-f)<<endl;

    }

    float D[a][b];
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
        {
            D[i][j]=A[i][j]-(e*II[i][j]);
        }
    }

    float det=1;
    float sign=1;

    for (int k=0; k<a; k++)
    {
        float max=abs(D[k][k]);
        int index=k;
        float temp=0;


        for(int i=k; i<a; i++)
        {
            if(abs(D[i][k])>max)
            {
                max=D[i][k];
                index=i;
            }
            else continue;
        }

        if(index!=k)
        {
            sign=sign*(-1);
        }


        for(int i=0; i<a; i++)
        {
            temp=D[k][i];
            D[k][i]=D[index][i];
            D[index][i]=temp;
        }



        for(int m=k+1; m<a; m++)
        {
            float val=D[m][k]/D[k][k];
            for(int l=k; l<a; l++)
            {
                D[m][l] = D[m][l] - (val*D[k][l]);
            }
        }
    }

    for(int i=0; i<a; i++)
    {
        det=det*D[i][i];

    }

    float determinant=det*sign;
    cout<<endl<<"Determinant is : "<<determinant<<endl;
    if(abs(determinant)<pow(10,-5)) e=e;
    else e=e*(-1);

    cout<<" One eigenvalue is : " << e << endl;

    cout<<endl<<"The eigenvector corresponding to above eigenvalue is : "<<endl;
    for (int i=0; i<a; i++)
    {

        cout<<V[i]<<endl;

    }
    cout<<endl;


    int k=0;
    while(k<b)
    {
        float d=A[k][k];

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
                for(int j=0; j<b; j++)
                {
                    A[i][j]=A[i][j]- (c)*A[k][j];

                    if (abs(A[i][j])<pow(10,-8)) A[i][j]=0;

                    I[i][j]=I[i][j]- (c)*I[k][j];

                    if (abs(I[i][j])<pow(10,-8)) I[i][j]=0;
                }
            }
        }

        k=k+1;
    }


    cout<<endl;

    cout<<"Inverse of A is: " <<endl;
    for (int i=0; i<a; i++)
    {
        cout<<endl;
        for(int j=0; j<b; j++)
        {
            cout<<I[i][j]<<" ";
        }
    }

    cout<<endl;

    cout<<"A gets converted to: " <<endl;
    for (int i=0; i<a; i++)
    {
        cout<<endl;
        for(int j=0; j<b; j++)
        {
            cout<<A[i][j]<<" ";
        }
    }

    float e1=100;
    float f1=50;

    while(abs(e1-f1)>=error)
    {

        f1=e1;

        for (int r=0; r<a; r++)
        {
            C[r]= 0;
            for(int k=0; k<a; k++)
            {
                C[r]+=I[r][k]*W[k];
            }

        }

        float d=0;
        for(int t=0; t<a; t++)
        {
            d = d + pow(C[t],2);
        }

        e1= sqrt(d);

        for(int y=0; y<a; y++)
        {

            W[y]=C[y]/e1;
        }
        //cout<<endl<<"Error is: "<<abs(e1-f1)<<endl;

    }

    float E[a][a];
    for(int i=0; i<a; i++)
    {
        for(int j=0; j<b; j++)
        {
            E[i][j]=I[i][j]-(e1*II[i][j]);
        }
    }

    float det1=1;
    float sign1=1;

    for (int k=0; k<a; k++)
    {
        float max=abs(E[k][k]);
        int index=k;
        float temp=0;


        for(int i=k; i<a; i++)
        {
            if(abs(E[i][k])>max)
            {
                max=E[i][k];
                index=i;
            }
            else continue;
        }

        if(index!=k)
        {
            sign1=sign1*(-1);
        }


        for(int i=0; i<a; i++)
        {
            temp=E[k][i];
            E[k][i]=E[index][i];
            E[index][i]=temp;
        }



        for(int m=k+1; m<a; m++)
        {
            float val=E[m][k]/E[k][k];
            for(int l=k; l<a; l++)
            {
                E[m][l] = E[m][l] - (val*E[k][l]);
            }
        }
    }

    for(int i=0; i<a; i++)
    {
        det1=det1*E[i][i];

    }

    float determinant1=det1*sign1;
    cout<<endl<<"Determinant is : "<<determinant1<<endl;
    if(abs(determinant1)<pow(10,-5)) e1=e1;
    else e1=e1*(-1);

    cout<<" second eigenvalue is : " << 1/e1 << endl;

    cout<<endl<<"The eigenvector corresponding to above eigenvalue is: "<<endl;
    for (int i=0; i<a; i++)
    {

        cout<<W[i]<<endl;

    }
    cout<<endl;

    float trace=0;
    for(int i=0; i<a; i++)
    {
        trace+=AA[i][i];
    }

    cout<<endl<<"Third eigenvalue is: "<< (trace-(1/e1)-e)<<endl;
}




