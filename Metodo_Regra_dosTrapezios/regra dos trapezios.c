#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define e 2.71828182845905
#define pi 3.14159265358979

# define red 250,0,0
#define wi 250, 250,250 
#define scala 1000
/**Edite sua f(x) para obter aproximacoes de outras funcoes;**/

double f(double x){
	return x*x*x;
}
void graficoPPM(char mat[][scala]);
void graficANAlise(char *gp,double *x, double *fx,double maior, double menor,int pontos,double deltaz,double a);

int main(){
		double a,b,h,soma=0;
		double *fx;
		double *x;
		int *ti; 
		int pontos =200 ;
		int i, y=5;
		
		double maior,menor;
		char grafic[scala][scala]={0};

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
			if(i==0){
				maior =menor = fx[i];
			}else {
				maior = maior>fx[i]?maior:fx[i];
				menor = menor<fx[i]?menor:fx[i];
			}
		}
		graficANAlise(&grafic[0][0],x,fx,maior,menor,pontos,b-a,a);
		soma = (h/2.0)*soma;
		printf("\n=========================================\n\n         A aproximacao = %lf\n\n=========================================\n",soma);
		graficoPPM(grafic);
		//printa(grafic);
		free(fx);
		free(ti);
		free(x);
		system("start Grafico.ppm");
}


void graficoPPM(char mat[][scala]) {
    /* 
    # NetPPM: https://en.wikipedia.org/wiki/Netpbm_format
    # The part above is the header
    # "P3" means this is a RGB color image in ASCII
    # "3 2" is the width and height of the image in pixels
    # "255" is the maximum value for each color
    # The part below is image data: RGB triplets
     */
    FILE * arquivo;
    int i, j ,k ;
    arquivo = fopen("Grafico.ppm", "w");
    fprintf(arquivo, "P3\n%d %d\n255\n# Pixels:\n", scala, scala);
    for(i = 0; i<scala;i++) {
        for(j = 0; j < scala; j++) {
        	if(mat[i][j]== 3 ){
            			fprintf(arquivo, "%d\t%d\t%d\t\t",red);
			}else {
            			fprintf(arquivo, "%d\t%d\t%d\t\t",wi);
			}
        }    
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}
double norma(double z, double y){
	return pow(z*z+y*y,0.5);
}
void graficANAlise(char *gp,double *x, double *fx,double maior, double menor,int pontos,double deltaz,double a){
	int i =0;
	
	double t,az,ay,cy,cz,y ,z,delta = maior-menor, normap;
// ZoY
	for(i=0;i<pontos;i++){
		y = (maior - fx[i])*(scala-1)/(delta);
		z =  (a+x[i])*(scala-1)/(deltaz);
		gp[(int)(((int)y)*scala+((int)z))]=3;
		if(i>0 ){
			az= (a+x[i-1])*(scala-1)/(deltaz);
			ay = (maior - fx[i-1])*(scala-1)/(delta);
			cz =  z - az;
			cy =  y - ay;
			if((int)cz != (int) z){
			normap = (z-az)/cz;
			}else {
				normap = (y-ay)/cy;
			}
			for(t=0;t<normap;t+=0.001){
					gp[(int)((int)(ay+cy*t)*scala+(int)(az+cz*t))]=3;
			}
		}
		
	}
	/*
	maior -menor = delta fx
	
		  maior - menor = 499
	      maior  -  fx[i]     =  y
	      y(maior - menor ) = (maior - fx)499
	      
	      y = (maior - fx[i])499/
	             (delta)
	
	b-a    =  499
	a+x[i] = z
	
	(b-a)z= (a+x[i])*499;
	
	z = (a+x[i])*499/
	        deltaz
	  * 
	*   *        *  
	     *     *
	        *
	*/
}
