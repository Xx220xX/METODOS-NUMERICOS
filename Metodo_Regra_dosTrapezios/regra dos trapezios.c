#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define e 2.71828182845905
#define pi 3.14159265358979

/**Edite sua f(x) para obter aproximacoes de outras funcoes;**/

double f(double x){
	return cos(x);
}

int main(){
		double a,b,h,soma=0;
		double *fx;
		double *x;
		int *ti; 
		int pontos;
		int i, y=5;
		
		printf("digite o valor de a :");
		scanf("%lf",&a);
		printf("digite o valor de b :");
		scanf("%lf",&b);
		printf("numero de pontos que vai dividir: ");
		scanf("%d",&pontos);
		 h = (b-a)/(pontos-1);
		printf("tabela : h = %lf\n\n",h);
		x =(double *) calloc(pontos,sizeof(double));
		fx = (double *)calloc(pontos,sizeof(double));
		ti =(int *) calloc(pontos,sizeof(int));
		for(i=0;i<pontos;i++){
			x[i]=a+i*h;
			fx[i]=f(x[i]);
			if(i==0){
				soma+=fx[i];
			}else if( i+1== pontos){
				soma+=fx[i];
			}else{
				soma+=2*fx[i];				
			}
			printf("    | x[%d] = %.4lf           ",i, x[i] );
			printf("|f(x[%d] ) = %.4lf \n",i,fx[i]);
			
		}
	soma = (h/2.0)*soma;
		printf("\n=========================================\n\n         A aproximacao = %lf\n\n=========================================\n",soma);
		free(fx);
		free(ti);
		free(x);
}
