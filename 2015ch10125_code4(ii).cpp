#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;


int main() {

ifstream myfile("input_3x3.dat",ios::in);
int n,row,col,sign=1;
float det=1;
myfile>>row>>col;
if(row!=col) {
cout << "Determinant not possible!"<<endl;
return 0;
}

n=col;
float A[n][n];
for (int i=0;i<n;i++) {
for (int j=0;j<n;j++) {
myfile>>A[i][j];
}
}


for (int k=0;k<n;k++) {
float max=abs(A[k][k]);
int index=k;
float temp=0;

for(int i=k;i<n;i++) {
if(abs(A[i][k])>max) {
max=A[i][k];
index=i;
}
else continue;
}

if(index!=k){
sign=sign*(-1);
}


for(int i=0;i<n;i++){
temp=A[k][i];
A[k][i]=A[index][i];
A[index][i]=temp;
}



for(int m=k+1;m<n;m++) {
float val=A[m][k]/A[k][k];
for(int l=k;l<n;l++){
//float val=A[m][k];
A[m][l] = A[m][l] - (val*A[k][l]);
}
}
}

for(int i=0;i<n;i++)
    {
        det=det*A[i][i];
        
    }
    
float determinant=det*sign;
cout<<"Determinant of matrix : " << determinant <<endl;
}





