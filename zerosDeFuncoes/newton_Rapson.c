#include <stdio.h>
#include <math.h>

double f(double x) {
    return sin(x);
}

double error(double x0, double x1, int relativo) {
    double erro = x1 - x0;
    return relativo ? erro / x1 : erro;
}

double derivada(double x) {
    double h = 0.0000000000001;
    return (f(x + h) - f(x - h)) / h;
}

double newtonIteract(double x0) {
    return x0 - f(x0) / derivada(x0);
}

int main() {
    double erro = 0.0;
    int i = 0;
    double x0 = 3, x1;
    double erroAtual;
    printf("x%d = %.17lf\n", i, x0);
    for (i = 0;; ++i) {
        x1 = newtonIteract(x0);
   
        printf("x%d = %.17lf\n", i, x1);
        if (  error(x0, x1, 0) < erro) {
            erroAtual = error(x0, x1, 0);
            printf("fim x = %.17lf\ncom f(x) = %.17lf\nerro = %lf", x1, f(x1), erroAtual);
            break;
        } else if (x1 == x0) {
            printf("repetiu\nfim x = %.17lf\ncom f(x) = %.17lf\nerro = %.18lf", x1, f(x1), erroAtual);
            break;
        }
        erroAtual = error(x0, x1, 1);
        x0 = x1;
    }
    return 0;
}
