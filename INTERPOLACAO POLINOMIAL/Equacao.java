
import java.util.Locale;

public class Equacao {
    private double[] coef;
    private static int casasDecimais = 4;

    public Equacao(double constante, double variavel) {
        this(new double[]{constante, variavel});
    }

    public static int porcentagem(int total, int atual) {
        return (int) (((double) atual * 100d) / (double) total);
    }

    public static abstract class Lagrage {
        int ordem;
        Tabela pontos;

        public Lagrage(Tabela tabela, int grauDopolinomio) {
            this.ordem = grauDopolinomio;
            pontos = tabela;
        }

        abstract void onProgres(int progress);

        abstract void onFinish(String polinomio);

        abstract void msgStatus(String msg);

        private Equacao gerarLi(int i, int ordem, Tabela pontos) {//gera o termo Li
            Equacao numerador = new Equacao(new double[]{1});
            double denominador = 1;
            msgStatus("gerando L" + i);
            for (int j = 0; j <= ordem; j++) {
                if (j == i) continue;
                onProgres((int) (100d * (double) j / (double) ordem));
                numerador = multiplicaCoef(numerador, -pontos.getX(j), 1);
                denominador *= pontos.getX(i) - pontos.getX(j);
            }
            return multiplicaCoef(numerador, pontos.getY(i) / denominador, 0);
        }

        public void gerarPn() {
            if (pontos.possuiPontos(ordem)) {
                Equacao polinomioDelaGrange = new Equacao(new double[]{0});
                for (int i = 0; i <= ordem; i++) {
                    polinomioDelaGrange = Equacao.somaCoef(polinomioDelaGrange, gerarLi(i, ordem, pontos));
                }
                onFinish(polinomioDelaGrange.toString());
            } else {
                msgStatus(" pontos insuficientes para gerar um polinomio de grau ");
                onFinish("Erro!!!");
            }
        }

    }


    public static class Tabela {
        private int pontos;
        private double[] x;
        private double[] y;

        public Tabela() {
            this.x = new double[0];
            this.y = new double[0];
            this.pontos = 0;
            atualizar();
        }

        public Tabela(double[] x, double[] y) {
            this.x = x;
            this.y = y;
            atualizar();
        }

        public void atualizar() {
            this.pontos = this.x.length > this.y.length ? this.y.length : this.x.length;
        }

        public void delet(int position) {
            position /= 2;
            double[] aux = new double[(this.x.length - 1)];
            int j = 0;
            int j2 = 0;
            for (int i = 0; i < this.x.length; i++) {
                if (i != position) {
                    aux[j2] = this.x[i];
                    j2++;
                }
            }
            this.x = aux;
            aux = new double[(this.y.length - 1)];
            for (j2 = 0; j2 < this.y.length; j2++) {
                if (j2 != position) {
                    aux[j] = this.y[j2];
                    j++;
                }
            }
            this.y = aux;
            atualizar();
        }

        public void deletTabela() {
            this.x = new double[0];
            this.y = new double[0];
        }

        public int getNumberPontos() {
            return this.pontos;
        }

        public Double[] getPontos() {
            Double[] aux = new Double[(this.x.length * 2)];
            int j = 0;
            for (int i = 0; i < this.x.length * 2; i++) {
                if (i % 2 == 0) {
                    aux[i] = Double.valueOf(this.x[j]);
                } else {
                    aux[i] = Double.valueOf(this.y[j]);
                    j++;
                }
            }
            return aux;
        }

        public double getX(int i) {
            if (this.x[i] == -0.0d) this.x[i] = 0.0d;
            return this.x[i];
        }

        public double getY(int i) {
            if (this.y[i] == -0.0d) this.y[i] = 0.0d;

            return this.y[i];
        }

        public void newPoint() {
            double[] aux = new double[(this.x.length + 1)];
            for (int i = 0; i < this.x.length; i++) {
                aux[i] = this.x[i];
            }
            this.x = aux;
            aux = new double[(this.x.length + 1)];
            for (int i2 = 0; i2 < this.y.length; i2++) {
                aux[i2] = this.y[i2];
            }
            this.y = aux;
            atualizar();
        }

        public boolean possuiPontos(int n) {
            return n >= 0 && n < this.pontos;
        }

        public void setX(int position, String s) {
            Double valor;
            try {
                valor = Double.valueOf(s);
            } catch (Exception e) {
                valor = Double.valueOf(0.0d);
            }
            this.x[position] = valor.doubleValue();
        }

        public void setY(int position, String s) {
            Double valor;
            try {
                valor = Double.valueOf(s);
            } catch (Exception e) {
                valor = Double.valueOf(0.0d);
            }
            this.y[position] = valor.doubleValue();
        }

    }

    public Equacao(double[] coef) {
        this.coef = coef;
    }

    private static String doubleToString(double v) {
        long b = (long) v;
        if (v - (double) b != 0.0d) {
            String formato = "%." + casasDecimais + "f";
            return String.format(Locale.US, formato, v);
        } else {
            return b + "";
        }
    }

    //4x^4 +6x^3+7x^2+4x+5
    //5,4,7,6,4
    public static Equacao multiplicaCoef(Equacao a, double coef, double x) {
        return multiplicaCoef(a, new Equacao(new double[]{coef, x}));
    }

    private static Equacao multiplicaCoef(Equacao a, Equacao b) {
        a.simplificar();
        b.simplificar();
        double[] aux = new double[(a.length() + b.length())];
        for (int i = 0; i < b.length(); i++) {
            for (int j = 0; j < a.length(); j++) {
                int i2 = i + j;
                aux[i2] = aux[i2] + (a.getCoef(j) * b.getCoef(i));
            }
        }
        return new Equacao(aux);
    }

    private void simplificar() {
        double aux[] = null;
        boolean isValid = false;
        int i = coef.length - 1;
        while (i >= 0) {
            if (coef[i] == -0.0d) {
                coef[i] = 0.0d;
            }
            if (!(coef[i] == 0.0d || isValid)) {
                aux = new double[(i + 1)];
                isValid = true;
            }
            if (isValid) {
                aux[i] = coef[i];
            }
            i--;
        }
        if (aux == null) {
            aux = new double[]{0.0d};
        }
        this.coef = aux;
    }

    public static Equacao somaCoef(Equacao a, Equacao b) {
        a.simplificar();
        b.simplificar();
        int ordem = b.length() > a.length() ? b.length() : a.length();
        double[] aux = new double[ordem];
        for (int i = 0; i < ordem; i++) {
            aux[i] = 0.0d;
            if (i < b.length()) {
                aux[i] = aux[i] + b.getCoef(i);
            }
            if (i < a.length()) {
                aux[i] = aux[i] + a.getCoef(i);
            }
        }
        return new Equacao(aux);
    }

    public double getCoef(int i) {
        return this.coef[i];
    }

    public int length() {
        return this.coef.length;
    }

    @Override
    public String toString() {
        simplificar();
        StringBuilder str = new StringBuilder();
        boolean mostrei = false;
        int i = length() - 1;
        double co;
        while (i >= 0) {
            co = coef[i];
            if (co != 0.0d) {
                if (co < 0) {
                    str.append(" - ");
                    co = -co;
                } else if (mostrei) {
                    str.append(" + ");
                }
                if (co != 1 || i == 0) {
                    str.append(doubleToString(co));
                }
                if (i > 0) {
                    str.append("x");
                }
                if (i > 1) {
                    str.append("^" + i);
                }
                mostrei = true;
            }
            i--;
        }
        return str.toString();
    }

    public static abstract class Newton {
        private StringBuilder polinomio;
        private double diferencasDivididas[];
        private Tabela pontos;
        int ordem;

        public Newton(Tabela pontos, int ordem) {
            this.pontos = pontos;
            this.ordem = ordem;

        }

        protected void calculaDifDiv() {
            diferencasDivididas = new double[ordem + 1];
            diferencasDivididas[0] = pontos.getY(0);
            class Dif {
                double v[] = new double[5];
            }
            class Tabelinha {
                public Tabelinha(Dif[] n) {
                    this.n = n;
                }

                Dif n[];
            }
            Tabelinha t[] = new Tabelinha[ordem + 1];
            setMsgDifdiv(gerarDif(0), diferencasDivididas[0]);
            for (int i = 1; i <= ordem; i++) {
                t[i] = new Tabelinha(new Dif[ordem + 1 - i]);
                progress(porcentagem(ordem + 1, i));
                msgStatus("calculando diferença dividida de ordem " + i);
                for (int j = 0; j < ordem + 1 - i; j++) {
                    t[i].n[j] = new Dif();
                    if (i == 1) {
                        t[i].n[j].v[0] = pontos.getY(i + j);
                        t[i].n[j].v[1] = pontos.getY(i + j - 1);
                        t[i].n[j].v[2] = pontos.getX(i + j);
                        t[i].n[j].v[3] = pontos.getX(i + j - 1);
                    } else {
                        t[i].n[j].v[0] = t[i - 1].n[j + 1].v[4];
                        t[i].n[j].v[1] = t[i - 1].n[j].v[4];
                        t[i].n[j].v[2] = t[i - 1].n[j + 1].v[2];
                        t[i].n[j].v[3] = t[i - 1].n[j].v[3];
                    }
                    t[i].n[j].v[4] = (t[i].n[j].v[0] - t[i].n[j].v[1]) / (t[i].n[j].v[2] - t[i].n[j].v[3]);
                }
                diferencasDivididas[i] = t[i].n[0].v[4];
                setMsgDifdiv(gerarDif(i), diferencasDivididas[i]);

            }
        }

        abstract void onFinish(String polinomio, String polinomioCompleto);

        abstract void setMsgDifdiv(String str, double d);

        abstract void msgStatus(String msg);

        abstract void progress(int porcentagem);

        /***
         recursive form
         private  double difDiv( int ordemRequerida, int inicial) {
         return ordemRequerida == 0 ? pontos.getY(inicial) : (difDiv( ordemRequerida - 1, inicial + 1) - difDiv( ordemRequerida - 1, inicial)) / (pontos.getX(inicial + ordemRequerida) - pontos.getX(inicial));
         }
         */
        private String gerarDif(int ordem) {
            StringBuilder s = new StringBuilder("F[");
            for (int i = 0; i <= ordem; i++) {
                s.append("x");
                s.append(i);
                if (i < ordem) {
                    s.append(",");
                }
            }
            s.append("] = ");
            return s.toString();
        }

        public void gerarPn() {
            if (!pontos.possuiPontos(ordem)) {
                onFinish("ERRO!!!::Pontos insuficientes", "");
                return;
            }
            calculaDifDiv();
            polinomio = new StringBuilder();
            Equacao fim = new Equacao(0d, 0d);
            for (int i = 0; i <= ordem; i++) {
                fim = somaCoef(fim, termo(i, pontos, ordem));
                if (i < ordem) {
                    polinomio.append(" + ");
                }
            }
            onFinish(fim.toString(), polinomio.toString());
            polinomio = null;
        }

        private Equacao termo(int i, Tabela pontos, int ordem) {

            double difdiv = difDivOtm(i);//calcula diferenca aki
            Equacao terminho = new Equacao(1d, 0d);

            for (int j = 0; j < i; j++) {
                polinomio.append("(x ");
                polinomio.append((pontos.getX(j) >= 0.0d) ? ("- " + doubleToString(pontos.getX(j))) : ("+ " + (doubleToString(-pontos.getX(j)))));
                polinomio.append(")*");
                terminho = multiplicaCoef(terminho, -pontos.getX(j), 1);
            }
            polinomio.append((difdiv < 0 ? ("(" + doubleToString(difdiv) + ")") : (doubleToString(difdiv))));

            return multiplicaCoef(terminho, difdiv, 0);

        }

        private double difDivOtm(int i) {
            return diferencasDivididas[i];
        }


    }
}
