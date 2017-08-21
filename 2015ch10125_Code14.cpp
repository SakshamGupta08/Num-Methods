#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

float function(float x,float A[21][2],float d2f[21])
{
    float F;
    int index;
    for(int i=0; i<20; i++)
    {
        if (A[i][0]<=x && A[i+1][0]>=x) index=i;
    }
    F=((d2f[index]*pow((x-A[index+1][0]),3))/(6*(A[index][0]-A[index+1][0]))) + ((d2f[index+1]*pow((x-A[index][0]),3))/(6*(A[index+1][0]-A[index][0])));
    F+=((A[index+1][1]/(A[index+1][0]-A[index][0]))-(d2f[index+1]*(A[index+1][0]-A[index][0])/6))*(x-A[index][0]);
    F+=((A[index][1]/(A[index][0]-A[index+1][0]))-(d2f[index]*(A[index][0]-A[index+1][0])/6))*(x-A[index+1][0]);
    return F;
}


float cent_diff(float x,float A[21][2],float d2f[21])
{

    int index;
    for(int i=0; i<20; i++)
    {
        if (A[i][0]<=x && A[i+1][0]>=x) index=i;
    }
    index=index;
    float ans= A[index+2][1]+A[index-2][1]- 2*A[index][1];
    return ans;
}

/*int fact(int n)
{
    int prod=1;
    for(int i=1; i<=n; i++)
    {
        prod=prod*i;
    }
    return prod;
}

float div_diff(float x,float A[21][2])
{
    float B[21];
    for(int i=0; i<21; i++)
    {
        B[i]=A[i][1];
    }
    float ans=A[0][1];
    for (float count=1; count<21; count++)
    {
        for(int i=0; i<20; i++)
        {
            B[i]=B[i+1]-B[i];
        }
        float prodnum=1;
        int j=0;
        while (j<count)
        {
            prodnum=prodnum*(x-A[j][0]);
            j++;
        }
        float h=0.5;
        ans=ans+((B[0]*prodnum)/(pow(h,count)*fact(count)));
    }
    return ans;
}*/

float Lagrange(float x,float A[21][2])
{

    float ans=0;
    float prodden;
    for(int i=0; i<21; i++)
    {
        float prodnum=A[i][1];
        for(int j=0; j<21; j++)
        {
            if(j!=i)
            {
                prodnum=prodnum*(x-A[j][0]);
            }
        }
        prodden=1;
        for(int j=0; j<21; j++)
        {
            if(j!=i)
            {
                prodden=prodden*(A[i][0]-A[j][0]);
            }
        }
        ans=ans+(prodnum/prodden);
    }
    return ans;
}

int main()
{
    ifstream myfile;
    myfile.open("xy.dat",ios::in);
    float A[21][2];
    for (int i=0; i<21; i++)
    {
        for (int j=0; j<2; j++)
        {
            myfile>>A[i][j];

        }
    }
    myfile.clear();
    myfile.close();

    /* for (int i=0; i<21; i++)
     {
         cout<<endl;
         for (int j=0; j<2; j++)
         {
             cout<<A[i][j]<<" ";

         }
     }*/

    float double_der[19];
    float M[19][19];
    float N[19];
    for(int i=0; i<19; i++)
    {

        N[i]=6*(((A[i+2][1]-A[i+1][1])/(A[i+2][0]-A[i+1][0]))-((A[i+1][1]-A[i][1])/(A[i+1][0]-A[i][0])));
    }

    for(int i=0; i<19; i++)
    {
        M[i][i-1]=A[i+1][0]-A[i][0];
        M[i][i]=2*(A[i+2][0]-A[i][0]);
        M[i][i+1]=A[i+2][0]-A[i+1][0];
        for(int k=0; k<19; k++)
        {
            if(k!=i&&k!=(i+1)&&k!=(i-1))
            {
                M[i][k]=0;
            }
        }
    }

    cout<<endl<<endl;
    cout<<"N matrix is"<<endl;
    for(int j=0; j<19; j++) cout<<N[j]<<endl;

    cout<<endl;
    cout<<"M matrix is: " <<endl;
    for(int a=0; a<19; a++)
    {
        cout<<endl;
        for(int b=0; b<19; b++)
        {
            cout<<M[a][b]<<" ";
        }
    }

    float temp1,temp2;

    int k=0;
    while(k<19)
    {


        int index=k;
        int l;
        float max=M[k][k];
        for(l=k; l<19; l++)
        {
            if(max<abs(M[l][k]))
            {
                max= M[l][k];
                index = l;
            }
        }

        for(int r=0; r<19 ; r++)
        {
            temp1 = M[k][r];
            M[k][r] = M[index][r];
            M[index][r] = temp1;
        }

        for(int r=0; r<19; r++)
        {
            temp2=N[k];
            N[k]=N[index];
            N[index]=temp2;
        }

        for(int i=k+1; i<19; i++)
        {
            double c= M[i][k]/M[k][k];
            N[i]=N[i] - (c)*N[k];
            if (abs(N[i])<pow(10,-8)) N[i]=0;

            for(int j=k; j<19; j++)
            {
                M[i][j]=M[i][j]- (c)*M[k][j];

                if (abs(M[i][j])<pow(10,-8)) M[i][j]=0;

            }
        }

        k=k+1;
    }

    double_der[18]=(N[18]/(M[18][18]));

    for(int i=17; i>=0; i--)
    {

        double sum=0;
        for(int j=i+1; j<19; j++)
        {
            sum=sum+ (M[i][j]*double_der[j]);
        }

        double_der[i]=(N[i]-sum)/M[i][i];
    }
    cout<<endl;

    float d2f[21];
    d2f[0]=d2f[20]=0;
    for(int i=1,j=0; i<20,j<19; i++,j++)
    {
        d2f[i]=double_der[j];
    }

    cout<<"Double derivatives are: "<<endl;
    for(int i=0; i<21; i++)
    {
        cout<<d2f[i]<<endl;

    }

    float x;
    cout<<"Value of x is:" <<endl;
    cin>>x;
    cout<<"Value of function :"<<function(x,A,d2f)<<endl;

    ofstream outputfile;
    outputfile.open("spline.dat");

    for(x=-5; x<=5; x=x+0.1)
    {
        outputfile<<x<<" "<<function(x,A,d2f)<<endl;
    }

    cout<<endl;
    float d2f0=cent_diff(0,A,d2f);
    float d2f1=cent_diff(1,A,d2f);
    cout<<"Value of f'' at 0 is "<<d2f0<<endl;
    cout<<"Value of f'' at 1 is "<<d2f1<<endl;

    //Divided Difference
    ofstream outfile;
    outfile.open("xy20.txt");
    for(x=-5; x<=5; x=x+0.1)
    {
        outfile<<x<<" "<<Lagrange(x,A)<<endl;
    }

    /*ofstream outfile2;
    outfile2.open("xy_div.dat");
    for(x=-5; x<=5; x=x+0.1)
    {
        outfile2<<x<<" "<<div_diff(x,A)<<endl;
    }*/

}
