Polinomio interpolador de Lagrange

Suponhamos que você possua **n** pontos de uma tabela da forma:

| x | y |
| :---- | :---- |
| x<sub>0</sub> | y<sub>0</sub> |
| x<sub>1</sub> | y<sub>1</sub> |
| ... | ... |
| x<sub>n-2</sub> | y<sub>n-2</sub> |
| x<sub>n-1</sub> | y<sub>n-1</sub> |

Esses pontos possui uma função f(x) = y

O polinomio interpolador  de lagrange fornece uma função P(x)
em que :

P(x) &approx; f(x)

e 

P(x) = a<sub>0</sub> + a<sub>1</sub>x + a<sub>2</sub>x^2 + ... + a<sub>n-2</sub>x^n-2 +a<sub>n-1</sub>x^n-1


 <img src="https://latex.codecogs.com/svg.latex?\Large&space;P(x)"> pode ser calculado usando as expressoes abaixo:

<img alight ="center" src="https://latex.codecogs.com/svg.latex?\Large&space;P(x) = \sum_{i=0}^{n-1}f(x_i)\ast L_i(x)" />

Onde :

<img src="https://latex.codecogs.com/svg.latex?\Large&space;L_i(x) = \prod_{j=0,j \neq i}^{n-1}\left(\frac{x-x_j}{x_i-x_j}\right)">


### [exemplo numerico](exemplo/lagrange.md)





