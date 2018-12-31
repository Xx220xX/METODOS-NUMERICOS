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

void geraLfi(int i, int n, double *x, double y, Equacao *l);

void multiplicarCoeficientes(Equacao *l, double x_n, double x_coef);

void printaL(Equacao *eq, FILE *f);

double *soma(Equacao *l, int n);

void lagrange(double *x, double *y, int pontos, FILE *arquivoParaResultado);

double getNumber(FILE *Iobuf);

void getPontos(double **x,double **y,int p,FILE *ioBuff);

int main(int contador, char **args) {
    printf("carregando arquivo\n");
   FILE *f,*TABELA = fopen("TABELA.txt", "r");
   if(!TABELA){
   	printf("Erro :\n     verifique se o arquivo 'TABELA.txt' existe\n");
   	exit(1);
   }
    double *x,*y;
    int  pontos =(int)  getNumber(TABELA);
    getPontos(&x,&y,pontos,TABELA);
    fclose(TABELA);
   printf("Foram carregados %d pontos \n",pontos);
    f = fopen("TABELA.txt", "a");
   printf("Gerando polinomido de grau %d \n",pontos-1);
    lagrange(x, y, pontos, f);
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
        achei =1;
     }
    return number/pow(10,decimais);
}

void lagrange(double *x, double *y, int pontos, FILE *arquivoParaResultado) {
    int i, n = pontos - 1;
    Equacao *l = (Equacao *) calloc(pontos, sizeof(Equacao)), final;
  fprintf(arquivoParaResultado, "\n_______________________________\n");
   fprintf(arquivoParaResultado,"Interpolando pela forma de lagrange\n");
    for (i = 0; i <= n; ++i) {
    	fprintf(arquivoParaResultado,"\nL%d(x)*f(x%d) = ",i,i);
        geraLfi(i, n, x, y[i], l + i);
        printaL(l + i, arquivoParaResultado);
    }
    final.coeficientes = soma(l, n);
    final.length = n + 1;
       fprintf(arquivoParaResultado,"\nPolinomio interpolado :)\n   y = ");
    printaL(&final, arquivoParaResultado);
    free(final.coeficientes);
    for (i = 0; i < n; ++i) {
        free(l[i].coeficientes);
    }
    free(l);
    fprintf(arquivoParaResultado, "_______________________________\n");
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

void printaL(Equacao *eq, FILE *f) {
    int i, jaPrintei = 0;
    for (i = eq->length - 1; i >= 0; i--) {
        if (eq->coeficientes[i] != 0.0 && eq->coeficientes[i] != -0.0) {
            if (jaPrintei) {
                fprintf(f, " %s ", eq->coeficientes[i] > 0.0 ? "+" : "-");
            } else {
                jaPrintei = 1;
            }
            if (i == 0 || (eq->coeficientes[i] != 1.0 && eq->coeficientes[i] != -1.0))
                fprintf(f, "%g", eq->coeficientes[i] < 0 ? -eq->coeficientes[i] : eq->coeficientes[i]);
            if (i > 0) {
                fprintf(f, "x");
            }
            if (i > 1) {
                fprintf(f, "^%d", i);
            }

        }
    }
    fprintf(f, "\n");
}

void geraLfi(int i, int n, double *x, double y, Equacao *l) {
    int k = 0;
    l->length = 1;
    l->coeficientes = (double *) calloc(1, sizeof(double));
    l->coeficientes[0] = 1;
    l->denominador = 1;
    for (k = 0; k <= n; ++k) {
        if (k == i) continue;
        multiplicarCoeficientes(l, -x[k], 1);
        l->denominador *= (x[i] - x[k]);
    }
    l->denominador = y / l->denominador;
    multiplicarCoeficientes(l, l->denominador, 0);
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


