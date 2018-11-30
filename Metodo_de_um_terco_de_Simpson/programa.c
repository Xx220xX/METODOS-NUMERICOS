#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define e 2.71828182845905
#define pi 3.14159265358979
double f(double x){
	return pow(e,x*x);
}

int main(){
		double a,b,h,soma=0;
		double *tabelafx;
		double *tabelax;
		int *tabelai; 
		int pontos;
		int i, y=5;
		
		printf("digite o intervalo:");
		scanf("%lf%lf",&a,&b);
		printf("numero de pontos: ");
		scanf("%d",&pontos);
		 h = (b-a)/(pontos-1);
		printf("tabela : h = %lf\n\n",h);
		tabelax =(double *) calloc(pontos,sizeof(double));
		tabelafx = (double *)calloc(pontos,sizeof(double));
		tabelai =(int *) calloc(pontos,sizeof(int));
		for(i=0;i<pontos;i++){
			tabelax[i]=a+i*h;
			tabelafx[i]=f(tabelax[i]);
		
			printf("    | x[%d] = %.4lf           ",i, tabelax[i] );
			printf("|f(x[%d] ) = %.4lf \n",i,tabelafx[i]);
			if(i>0 && i+1<pontos){
				if(i%2==0){
					soma+=2*tabelafx[i];
				}else{
					soma+=4*tabelafx[i];
				}
			}else{
					soma+=tabelafx[i];				
			}
		}
		soma= soma*h/3;
		printf("\n=========================================\n\n         A aproximacao = %lf\n\n=========================================\n",soma);
		free(tabelafx);
		free(tabelai);
		free(tabelax);
}
