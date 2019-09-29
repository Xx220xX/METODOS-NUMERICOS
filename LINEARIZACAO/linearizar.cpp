#include<iostream>
#include <cstring>

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <cmath>


class Points {
public:
    ~Points() {
        free(v);
    }

    int len = 0;
    double *v = 0;

    friend std::ostream &operator<<(std::ostream &os, Points &v) {
        for (int i = 0; i < v.len; i++) {
            os << v.v[i] << ' ';
        }
        return os;
    }

    double operator[](int a) {
        return v[a];
    }

    double media() {
        double s = 0;
        for (int i = 0; i < len; i++) {
            s += v[i];
        }
        return s / len;
    }

    std::string pythonArray() {
        std::string points = "[";
        for (int i = 0; i < len; ++i) {
            points += to_string(v[i]) + (i + 1 < len ? "," : "");
        }
        points += "]";
        return points;
    }

    static void plot(Points &a, Points &b, bool discret = false,std::string file = "pl") {//call cmd python
        std::string cmd ="";
        cmd += "import matplotlib.pyplot as plt\n";
        cmd += "plt.plot("+a.pythonArray()+","+b.pythonArray()+(discret?",'ro'":"")+",color='b'"+
                ")\n";
        cmd += "plt.show()\n";
        file+=".py";
        FILE *f = fopen(file.c_str(),"w");
        fprintf(f,"%s",cmd.c_str());
        fclose(f);
        system(file.c_str());
    }
    static void plot(Points &x, Points &y, double a, double b,bool discret = false,std::string file = "pl", bool line = false) {//call cmd python
        std::string cmd ="";
        cmd += "import matplotlib.pyplot as plt\n";
        cmd += "x = "+x.pythonArray()+"\n";
        cmd += "y1 = "+y.pythonArray()+"\n";
        cmd += "y2 = [";
        for (int i = 0; i < x.len; ++i) {
            cmd += to_string(x[i]*a+b)+(i+1<x.len?",":"");
        }
        cmd+="]\n";
        cmd += string("plt.plot(x,y1") + (discret?",'ro'":"")+",color='b'"+")\n";
        cmd += string("plt.plot(x,y2") + (discret?",'ro'":"")+",color='r'"+")\n";
        if(line){
            cmd += string("plt.plot(x,y1") +",color='b'"+")\n";
            cmd += string("plt.plot(x,y2") +",color='r'"+")\n";
        }
        cmd += "plt.ylabel('tensão[v]')\n";
        cmd += "plt.xlabel('corrente[I]')\n";
        cmd+= "plt.grid(True)\n";
        cmd+= "plt.title('Curto circuito')\n";
        cmd += "plt.show()\n";

        file+=".py";
        FILE *f = fopen(file.c_str(),"w");
        fprintf(f,"%s",cmd.c_str());
        fclose(f);
        system(file.c_str());
    }
};

void loadPoints(Points &x, Points &y, const char *fileName) {
    FILE *f = fopen(fileName, "r");
    char mode[10] = {0};
    fscanf(f, "%s", mode);
    int i = 0;
    double a, b;
    if (strcmp(mode, "and") == 0) {
        while (fscanf(f, "%lf %lf", &a, &b) != EOF) {
            i++;
            x.v = (double *) realloc(x.v, i * sizeof(double));
            y.v = (double *) realloc(y.v, i * sizeof(double));
            x.v[i - 1] = a;
            y.v[i - 1] = b;
            //cout << a << ' ' << b << endl;
        }
    }
    x.len = i;
    y.len = i;
    fclose(f);
}

double A(Points &x, Points &y, double b) {
    return y.media() - x.media() * b;
}

double B(Points &x, Points &y) {
    double x_medio = x.media(), y_medio = y.media(), num = 0, den = 0;
    for (int i = 0; i < x.len; i++) {
        num += (x[i] - x_medio) * (y[i] - y_medio);
        den += pow((x[i] - x_medio), 2);
    }
    return num / den;
}

void geraPontos(double a, double b, double begin, double finish, const char *fileName) {
    FILE *f = fopen(fileName, "w");
    fprintf(f, "and\n");
    for (; begin < finish; begin++) {
        fprintf(f, "%lf %lf\n", begin, begin * a + b);
    }
    fclose(f);
}
void geraPontos(double a, double b, Points &x, const char *fileName) {
    FILE *f = fopen(fileName, "w");
    fprintf(f, "and\n");
    for (int i=0;  i<x.len; i++) {
        fprintf(f, "%lf %lf\n",x[i], x[i] * a + b);
    }
    fclose(f);
}

int main() {
    Points x, y;
    loadPoints(x, y, "input.txt");
    double a, b;
    a = B(x, y);
    b = A(x, y, b);
    cout << a << "*x + " << b << endl;
    Points::plot(x,y,a,-0.025,true,"pl2");
    Points::plot(x,y,a,-0.025,true,"pl3",true);
   // geraPontos(a,b,x,"../input2.txt");

}
