#include<stdio.h>

double f(double x, double y) {
    return -2 * x * y - y * y;
}

int main() {
    int i;
    double xn = 0, yn = 1, xn_1, x_f = 0.5, yn_1, h = 0.1;
    do {
        printf("digite o valor de h: ");
        scanf("%lf", &h);
        if (h > 0)
            break;
        printf("h nao pode ser 0 \n");
    } while (1);
    printf("digite o valor de x[0]: ");
    scanf("%lf", &xn);
    printf("digite o valor de Y(x[0]): ");
    scanf("%lf", &yn);
    printf("digite o valor do ponto final : ");
    scanf("%lf", &x_f);

    printf("		n        x[n]        y[n]        f(x[n],y[n])        Y(x[n+1] )       \n");
    for (i = 0; xn < x_f + h;) {
        xn_1 = xn + h;
        yn_1 = yn + h * f(xn, yn);
        printf("		%d        %0.4lf\t\t%0.4lf\t\t%0.4lf\t\t  %0.4lf  \n", i++, xn, yn, f(xn, yn), yn_1);
        xn = xn_1;
        yn = yn_1;
    }
    return 0;
}
