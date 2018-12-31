#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#if  win32
 #define ABRIR_ARQUIVO() system("start TABELA.txt");
#elif unix
#define ABRIR_ARQUIVO() system("open TABELA.txt");
#else 
#define ABRIR_ARQUIVO() 
#endif

typedef struct {
    double *coeficientes;
    double denominador;
    int length;
} Equacao;

double difDiv(double *x,double *y,unsigned p, unsigned  i);

void newton(double *x, double *y, int pontos, FILE *arquivoParaResultado) ;

void multiplicarCoeficientes(Equacao *l, double x_n, double x_coef);

void printaL(Equacao *eq, FILE *f,int sinal);

double *soma(Equacao *l, int n);

double getNumber(FILE *Iobuf);

void getPontos(double **x,double **y,int p,FILE *ioBuff);

void printaDifdiv(int index,FILE *arq);

void printAllEq(Equacao *termo,int n,FILE *arq);

int main(int contador, char **args) {
    FILE *f,*TABELA = fopen("TABELA.txt", "r");
    if(!TABELA){
   	printf("Erro :\n     verifique se o arquivo 'TABELA.txt' existe\n");
   	exit(1);
   }
    double *x,*y;
    int  pontos =(int)  getNumber(TABELA);
    printf("carregando arquivo\n");
    getPontos(&x,&y,pontos,TABELA);
    fclose(TABELA);
    printf("Foram carregados %d pontos \n",pontos);
    f = fopen("TABELA.txt", "a");
    printf("Gerando polinomido de grau %d \n",pontos-1);
    newton(x, y, pontos,  f);
    printf("Processo finalizado \n Verifique seu arquivo \n");
    free(x);
    free(y);
    fclose(f);
   ABRIR_ARQUIVO();
}

double getNumber(FILE *Iobuf) {
    double number = 0;
    int c, decimais = 0, edecimal = 0, achei = 0;
    while (!feof(Iobuf)) {
        c = fgetc(Iobuf);
        if (c == '/' || c == '#') {
        	if(achei )break;
            while (!feof(Iobuf) && c!= '\n' && c!= '#' ){
            	c=fgetc(Iobuf) ;
            }
            continue;
        }
        if( c=='.'  && achei && !edecimal){
            edecimal =1;
            continue;
        }
        if(c <'0'|| c > '9'){
            if(achei)break;
            continue;
        }
        if(edecimal){
          decimais++;
        }
        number= number*10+(c-48);
        achei  = 1;
     }
    return number/pow(10,decimais);
}

void geratermo(int i, double *x,double *y, Equacao *termo,FILE *arq){
	double diferencaDividida = difDiv(x, y, i, 0);
	int j=0;
	fprintf(arq, "\n");
	
	printaDifdiv(i,arq);
	fprintf(arq," = %lf\n",diferencaDividida);
    
    termo->coeficientes=(double *)calloc(1, sizeof(double ));
	termo->coeficientes[0]=1.0;
	termo->length=1;
    for(;j<i;j++)
	       multiplicarCoeficientes(termo,- x[j], 1);
	fprintf(arq,"(");
    
    printaL(termo, arq,0);
    fprintf(arq,")*%g\n",diferencaDividida);
    	multiplicarCoeficientes(termo, diferencaDividida, 0);
}
void newton(double *x, double *y, int pontos, FILE *arquivoParaResultado) {
    int i, n = pontos - 1;
    //f(x0)+(x-x0)f[x0,x1]+(x-x0)(x-x1)f[x0,x1,x2]
    Equacao *termos= (Equacao *) calloc(pontos, sizeof(Equacao)), final;
  fprintf(arquivoParaResultado, "\n_______________________________\n");
   fprintf(arquivoParaResultado,"Interpolando pela forma de newton\n");
    for (i = 0; i <= n; ++i) {	
    	fprintf(arquivoParaResultado,"\ntermo %d:",i);
        geratermo(i,  x, y, termos + i,arquivoParaResultado);   
    }
    fprintf(arquivoParaResultado, "\n Pn(x) = ");
    printAllEq(termos,n,arquivoParaResultado);
    final.coeficientes = soma(termos, n);
    final.length = n + 1;
    fprintf(arquivoParaResultado,"\nPolinomio interpolado :)\n   y = ");
    printaL(&final, arquivoParaResultado,0);
    free(final.coeficientes);
    for (i = 0; i < n; ++i) {
        free(termos[i].coeficientes);
    }
    free(termos);
    fprintf(arquivoParaResultado, "\n_______________________________\n");
}
double difDiv(double *x,double *y,unsigned p, unsigned  i){
	if(p==0)return y[i];
	return (difDiv(x, y, p-1, i+1)-difDiv(x, y, p-1, i))/(x[i+p]-x[i]);
}
double *soma(Equacao *l, int n) {
    int i, j;
    double *coef = (double *) calloc(n + 1, sizeof(double));
    for (i = 0; i <= n; ++i) {
        for (j = 0; j < l[i].length; ++j) {
            coef[j] += l[i].coeficientes[j];
        }
    }
    return coef;
}

void printaL(Equacao *eq, FILE *f,int sinal) {
    int i, jaPrintei = 0;
    for (i = eq->length - 1; i >= 0; i--) {
        if (eq->coeficientes[i] != 0.0 && eq->coeficientes[i] != -0.0) {
            if (jaPrintei || sinal) {
                fprintf(f, " %s ", eq->coeficientes[i] > 0.0 ? "+" : "-");
                 	  } else {
                jaPrintei = 1;
            }
            if (i == 0 || (eq->coeficientes[i] != 1.0 && eq->coeficientes[i] != -1.0)){
                fprintf(f, "%g", eq->coeficientes[i] < 0 ? -eq->coeficientes[i] : eq->coeficientes[i]);
                 	   }  if (i > 0) {
                fprintf(f, "x");
            	 
            }
            if (i > 1) {
                fprintf(f, "^%d", i);
            }
        }
    }
}



void multiplicarCoeficientes(Equacao *l, double x_n, double x_coef) {
    double vet[2];
    double *coef = calloc(l->length + 1, sizeof(double));
    vet[0] = x_n;
    vet[1] = x_coef;
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < l->length; j++) {
            coef[i + j] += vet[i] * l->coeficientes[j];
        }
    }
    free(l->coeficientes);
    l->coeficientes = coef;
    l->length++;
}
void getPontos(double **x,double **y,int p,FILE *ioBuff){
   int i;double *ax,*ay;
   ax = (double *)calloc(p, sizeof(double ));
   ay = (double *)calloc(p, sizeof(double ));
   for(i=0;i<p;i++)
   ax[i] = getNumber(ioBuff);
   for(i=0;i<p;i++)
   ay[i] = getNumber(ioBuff);
  *x=ax;
  *y=ay;
}

void printaDifdiv(int index,FILE *arq){
	int i;
	fprintf(arq, "f[");
	for(i=0;i<=index;i++){
		fprintf(arq, "x%d%s",i,i<index?",":"");
	}
	fprintf( arq,"]");
}
void printAllEq(Equacao *termo,int n,FILE *arq){
	if(n<0)return;
	printAllEq(termo+1, n-1,arq);
	printaL(termo, arq,n);
}
