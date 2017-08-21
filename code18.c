#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){
    int i, n,j, k, p,s,m;
    float a[100][100],b[100],x[100],y[100], temp2, deter =1.0, max, temp, pivot, sum, sum1, phi, T=0;
for(i=1;i<=11;i++){
	y[i] = T;
	T= T+.1;
}
printf("Enter the value of phi \n");
	scanf("%g" , &phi);
	for(i=1 ;i<=10;i++){
		a[i][i] = -1*(2+ (phi*phi*.01));
	}
	for(i=2 ;i<=10;i++){
		a[i][i-1] = 1;
	}
	a[1][2] = 2;
	for(i=2 ;i<=9;i++){
		a[i][i+1] = 1;
	}
	for(i=1 ;i<=9;i++){
		b[i] = 0;
	}
	b[10] = -1;

   for(k=1; k<=10; k++){
        for(i=k+1; i<=10; i++){
		if(a[k][k]==0)break;
		pivot = a[i][k];
		b[i] = b[i] - b[k] * pivot/a[k][k];
		for(j=1; j<=10; j++){
		        a[i][j] -= pivot * a[k][j] / a[k][k];
		}
        }
    }
	for(i=10 ; i>=1; i--){
		sum = 0.0;
		for(j=10; j>=i+1; j--){
			sum = sum + a[i][j]*x[j];
		}
		x[i] = (b[i] - sum)/ a[i][i];
	}
 	FILE *fptr;
	fptr = fopen("xy20.dat" , "w");
	x[11] =1;
	for(j=1; j<=11; j++){
		fprintf(fptr, "%g %g \n" ,y[j] ,x[j]);
	}
fclose(fptr);
FILE *fptr1;
	fptr1 = fopen("y1.dat" , "w");
	for(j=1; j<=11; j++){
		fprintf(fptr1, "%g %g \n" ,y[j] ,(cosh(phi*y[j]))/cosh(phi));
	}
fclose(fptr1);

sum = 0;
for(i=2;i<=10;i+=2){
	sum=sum+(0.1/3)*(x[i-1]+4*x[i]+x[i+1]);
}
printf("The value of the integration is %g \n", sum);
printf("The analytical value of eta is %g \n", tanh(phi)/(phi));
return 0;
}
