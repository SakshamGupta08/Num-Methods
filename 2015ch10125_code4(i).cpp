#include <iostream>
#include <fstream>
using namespace std;

int main() {

ifstream myfile("input_3x3.dat",ios::in);
int n,row,col;
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
if(A[k][k]==0) {
cout<<"Can't be done by this method further"<<endl;
return 0;
}
}


for (int k=0;k<n;k++) {

//else{
for(int m=k+1;m<n;m++) {
float val=A[m][k]/A[k][k];
for(int l=k;l<n;l++){
//float val=A[m][k];
A[m][l] = A[m][l] - (val*A[k][l]);

}
}
}

for(int i=0;i<n;i++){
det=det*A[i][i];
}
cout<<"Determinant of matrix : " << det <<endl;
}





