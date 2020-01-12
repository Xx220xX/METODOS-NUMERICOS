### Interpolando em linguagem C
Antes de começarmos teremos que criar algumas funções ja que as unicas bibliotecas a serem usadas serão **stdio.h** e **stdlib.h**, para as funções **printf**, **calloc**, **free**
.
##### Funções auxiliares para polinomio
Devemos definir como representaremos nosso polinomio.
Para isso é criado a struct abaixo:

```C
typedef struct {
    double * coeficientes;
    int len;
}Polinomio;
```
> onde **coeficientes** é um ponteiro para armazenar os coeficientes de um polinomio e
> **len** é o tamanho da memoria alocada para o vetor. A posição do vetor indica o expoente.

Criaremos uma função para criar um Polinomio.

```C
Polinomio novoPolinomio(const double * v,int size){
    Polinomio ans= {0,size};
    ans.coeficientes = (double *)calloc(size,sizeof(double));
    if (v)
        for(size=size-1;size>=0;size--)
            ans.coeficientes[size] = v[size];
    return ans;
}
```

E já criando uma função para apagar o polinomio

```C
void apagarPolinomio(Polinomio p){
    if (p.coeficientes)
       free(p.coeficientes);
    p.len = 0;
}
```

Agora que possuimos  um polinomio iremos criar as funções de multiplicação e adição 

```C
Polinomio multPolinomio(Polinomio a,Polinomio b,int apaga_a,int apaga_b){
    Polinomio ans = novoPolinomio(0,a.len+b.len-1);
    int i,j;
    for (i=0;i<a.len;i++)
       for (j=0;j<b.len;j++)
           ans.coeficientes[i+j] += a.coeficientes[i]*b.coeficientes[j];
    if (apaga_a)
       apagarPolinomio(a);
    if (apaga_b)
       apagarPolinomio(b);
  return ans;
}
```
> A função recebe dois polinomios e dois inteiros.
> A multiplicação pode ser vista de duas maneiras, como a convolução de dois sinais ou utilizando uma propriedade exponencial (multiplica os coeficientes e soma os expoentes).
>
> As variaveis **apaga_a**  e **apaga_b** servem para  dizer se a função pode apagar os polinomios após feito a multiplicação.

```C
Polinomio somaPolinomio(Polinomio a,Polinomio b,int apaga_a,int apaga_b){
    int i;
    Polinomio ans;
    if (a.len>b.len){
       ans = a;
       a = b;
       b = ans;
    }
    ans = novoPolinomio(b.coeficientes,b.len);
    for (i=0;i<a.len;i++)
       ans.coeficientes[i] += a.coeficientes[i];
    if (apaga_a)
       apagarPolinomio(a);
    if (apaga_b)
       apagarPolinomio(b);
    return ans;
}
```
> Antes de realizar a soma é verificado qual polinomio tem maior grau, deixando sempre este como o polinomio **b**

Também podemos criar uma função para aplicar um valor x ao polinomio e obtermos o resultado.

```C
double evalPolinomio(Polinomio p,double x){
    double ans = 0, potencia = 1;
    int i;
    for (i=0;i<p.len;i++){
       ans += p.coeficientes[i] * potencia;
       potencia *= x;
    }
    return ans;
}
```


E por fim podemos tambem printar  um polinomio.

```C
 void printPolinomio(Polinomio p){
   int i;
   if (p.len>0)
      printf("%lf x^%d",p.coeficientes[p.len-1],p.len-1);
   for (i=p.len-2;i>=0;i--)
     printf(" + %lf x^%d",p.coeficientes[i],i);
}
```

> o **if** é para printar com a quantidade correta de " + " entre os termos.

### Interpolando
Finalmente hora de aplicar os conhecimentos de interpolação.

Faremos a interpolação em uma unica função, que retornará um polinomio.

Os techos de codigo a seguir correspodem a função **interpolarLagrage**

* cabeçalho

  ```C
  Polinomio  interpolarLagrange(double *x,double *y,int n);
  ```

  > suponharemos que os vetores **x** e **y** possuam tamanho maior ou igual a **n**, **n-1** corresponde ao grau do polinomio a ser encontrado.

* declaração e inicialização de variáveis 

  ```C
  int i,j;
  Polinomio P = {0},termo,lij=novoPolinomio(0,2);
  ```
  > As variáveis **i** e **j** são para o laço interativo.
  >
  > A variavel **P** é o polinomio que encontraremos P(x).
  > 
  > A variável **termo** será o polinomio gerado por cada <img src="https://latex.codecogs.com/svg.latex?\Large&space;f(x_i)\ast%20L_i(x)"/> .

E por fim a variavel lij é uma auxiliar para achar os polinomios <img alight ="center" src="https://latex.codecogs.com/svg.latex?\Large&space;L_i(x)" />

* Laços iterativos

  ```C
  for(i=0;i<n;i++){
       termo = novoPolinomio(0,1);
       termo.coeficiente[0] = y[i];
       for(j=0;i<n;j++){
          if(i==j) continue;
          lij.coeficientes[0] = -x[j]/(x[i]-x[j]); 
          lij.coeficientes[1] = 1/(x[i]-x[j]);
          termo = multPolinomio(termo,lij,1,0);
       }
       P = somaPolinomio(P,termo,1,1);
   }
  ```

  > A primeira e segunda linha do primeiro laço cria um polinomio com grau 0 com coeficiente igual a  <img alight ="center" src="https://latex.codecogs.com/svg.latex?\Large&space;f(x_i)=y[i]" />.
  > 
  > O segundo laço verifica se i==j caso verdadeiro ignora essa iteração com o comando **continue**.
  >
  > Nas duas linhas de baixo cria-se um polinomio de  grau 1 representando: <img alight ="center" src="https://latex.codecogs.com/svg.latex?\Large&space;(\frac{x}{x_i-x_j}+\frac{-xi}{x_i-x_j})" />
  >
  > Em seguida multiplica-se o termo pelo polinomio gerado, os parametros 1,0 significa para liberar a memoria da variável **termo** e manter  **lij**
  >
  > Ao sair do laço intermediario é feito a soma e armazenado na variável **P**

* Fim da função

  Agora so resta liberar as variaveis usadar e retornar o polinomio P

  ```C
   apagarPolinomio(lij);
   return P;
  ```

### codigo completo
```C
#include<stdio.h>
#include<stdlib.h>

typedef struct {
    double * coeficientes;
    int len;
}Polinomio;

Polinomio novoPolinomio(const double * v,int size){
    Polinomio ans= {0};
    ans.coeficientes = (double *)calloc(size,sizeof(double));
    ans.len = size;
    if (v)
        for(size=size-1;size>=0;size--)
            ans.coeficientes[size] = v[size];
    return ans;
}

void apagarPolinomio(Polinomio p){
    if (p.coeficientes)
       free(p.coeficientes);
    p.len = 0;
}
Polinomio multPolinomio(Polinomio a,Polinomio b,int apaga_a,int apaga_b){
    Polinomio ans = novoPolinomio(0,a.len+b.len-1);
    int i,j;
    for (i=0;i<a.len;i++)
       for (j=0;j<b.len;j++)
           ans.coeficientes[i+j] += a.coeficientes[i]*b.coeficientes[j];
    if (apaga_a)
       apagarPolinomio(a);
    if (apaga_b)
       apagarPolinomio(b);
    return ans;
}

Polinomio somaPolinomio(Polinomio a,Polinomio b,int apaga_a,int apaga_b){
    int i;
    Polinomio ans;
    if (a.len>b.len){
       ans = a;
       a = b;
       b = ans;
    }
    ans = novoPolinomio(b.coeficientes,b.len);
    for (i=0;i<a.len;i++)
       ans.coeficientes[i] += a.coeficientes[i];
    if (apaga_a)
       apagarPolinomio(a);
    if (apaga_b)
       apagarPolinomio(b);
    return ans;
}

double evalPolinomio(Polinomio p,double x){
    double ans = 0, potencia = 1;
    int i;
    for (i=0;i<p.len;i++){
       ans += p.coeficientes[i] * potencia;
       potencia *= x;
    }
    return ans;
}

void printPolinomio(Polinomio p){
   int i;
   printf("grau %d\n",p.len-1);
   if (p.len>0)
      printf("%lf x^%d",p.coeficientes[p.len-1],p.len-1);
   for (i=p.len-2;i>=0;i--)
     printf(" + %lf x^%d",p.coeficientes[i],i);
}

Polinomio  interpolarLagrange(double *x,double *y,int n){
  int i,j;
  Polinomio P = {0},termo,lij=novoPolinomio(0,2);

  for(i=0;i<n;i++){
     termo = novoPolinomio(0,1);
     termo.coeficientes[0] = y[i];
     for(j=0;j<n;j++){
        if(i==j) continue;
        lij.coeficientes[0] = -x[j]/(x[i]-x[j]); 
        lij.coeficientes[1] = 1/(x[i]-x[j]);
        termo = multPolinomio(termo,lij,1,0);
     }
     P = somaPolinomio(P,termo,1,1);
   }
   apagarPolinomio(lij);
   
   return P;
}
```

