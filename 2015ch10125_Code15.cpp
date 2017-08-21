#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main()
{
    int n=21;
    ifstream myfile;
    myfile.open("xy.dat",ios::in);
    float A[n][2];
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<2; j++)
        {
            myfile>>A[i][j];

        }
    }
    myfile.clear();
    myfile.close();
    if(n%2==0) cout<<"Can't be done using Simpson's one-third rule"<<endl;


 float h=0.5;
 float integral=0;
 for (int i=0;i<19;i=i+2){
 integral= integral+(h/3)*(A[i][1]+A[i+2][1]+4*A[i+1][1]);
 }
 cout<<"Integral value by Simpson's method :"<<integral<<endl;
}

