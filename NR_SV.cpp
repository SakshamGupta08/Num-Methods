
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main()
{
float B,A,Tr,Pr,F,w,P,V[200][200],R,T,Tc,Pc;
cout<<"Enter value of w: "<<endl;
cin>>w;
cout<<"Enter value of critical Temperature Tc : "<<endl;
cin>>Tc;
cout<<"Enter value of critical pressure Pc : "<<endl;
cin>>Pc;
cout<<"Enter value of Temperature: "<<endl;
cin>>T;
P=1;
//float Z;
float Z[3];
cout<<"Enter initial estimates of Z :" <<endl;
for(int i=0;i<3;i++){
cin>>Z[i];
}
//cin>>Z;
float Z_stat[3];
for(int i=0;i<3;i++){
    Z_stat[i]=Z[i];
}
int count=0;
while(P<100){
Pr=P/Pc;
Tr=T/Tc;
B=0.08664*Pr/Tr;
F=pow((1+(0.48+(1.574*w)-(0.176*w*w))*(1-pow(Tr,0.5))),2)/Tr;
A=0.42748*F*Pr/Tr;
R=82.05;

//cout<<"Value of A : "<<A<<endl;
//cout<<"Value of B : "<<B<<endl;

//Newton raphson
for(int i=0;i<3;i++){
Z[i]=Z_stat[i];
float ans=pow(Z[i],3)-pow(Z[i],2)+(Z[i]*(A-B-pow(B,2)))-A*B;
//cout<<ans<<endl<<endl;
while(abs(ans)> 0.00001){
    float der=3*pow(Z[i],2)-(2*Z[i]) + A-B-pow(B,2);
    Z[i]=Z[i]-(ans/der);
    //cout<<"Answer is : "<<ans<<endl;
    //cout<<"Der is : "<<der<<endl<<endl;
    ans=pow(Z[i],3)-pow(Z[i],2)+(Z[i]*(A-B-pow(B,2)))-A*B;
    //cout<<"New value of Z is : "<<Z[i]<<endl;
    //cout<<"New Ans is : "<<ans<<endl;
}
cout<<"Root is : "<<Z[i]<<endl;
V[count][i] = Z[i]*R*T/P;
}
//cout<<endl;
cout<<P<<endl;
P=P+1;
count++;
}

for(int i=0;i<count;i++){
        cout<<endl;
        for(int j=0;j<3;j++){
    cout<<V[i][j]<<endl;
}
//cout<< "At Pressure "<<P<<" Volume is "<<V<<endl;
}

}
