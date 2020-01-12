Polinomio interpolador de Lagrange
# Exemplo
### Dados
Dado a tabela abaixo **4** pontos

| i | x | y |
| :---- | :---- | :---- |
| 0 | 0 | 1 |
| 1 | 2 | 5 |
| 2 | 5 | 266 |
| 3 | 7 | 820 |

Como é um exemplo já conhecemos a função f(x)

<img src="https://latex.codecogs.com/svg.latex?\Large&space;f(x)=3x^3-4x^2-2x+1"/>

Mas em casos reais não conhecemos a função f(x), portanto encontraremos P(x).

##### Encontrando P(x)
> * Resolver somatorio 

> > <img src="https://latex.codecogs.com/svg.latex?\Large&space;P(x)=\sum_{i=0}^{n-1}f(x_i)\ast%20L_i(x)"/>
> 
> > <img src="https://latex.codecogs.com/svg.latex?\Large&space;P(x)=f(x_0)\ast%20L_0(x)+f(x_1)\ast%20L_1(x)+f(x_2)\ast%20L_2(x)+f(x_3)\ast%20L_3(x)"/>
> 
> > <img src="https://latex.codecogs.com/svg.latex?\Large&space;P(x)=1\ast%20L_0(x)+5\ast%20L_1(x)+266\ast%20L_2(x)+820\ast%20L_3(x)"/>

> * Encontrar as funções  <img alight ="center" src="https://latex.codecogs.com/svg.latex?\Large&space;L_i(x)"/>

>    <img src="https://latex.codecogs.com/svg.latex?\Large&space;L_i(x)=\prod_{j=0,j\neq%20i}^{n-1}\left(\frac{x-x_j}{x_i-x_j}\right)">
>   * <img alight ="center" src="https://latex.codecogs.com/svg.latex?\Large&space;L_0(x)"/>
> 
>    >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{(x-x_1)(x-x_2)(x-x_3)}{(x_0-x_1)(x_0-x_2)(x_0-x_3)}">  
>    >   
>    >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{(x-2)(x-5)(x-7)}{(0-2)(0-5)(0-7)}">
>    >    
>    >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{x^3-14x^2+59x-70}{-70}">
> 
>   * <img src="https://latex.codecogs.com/svg.latex?\Large&space;L_1(x)"/>
> 
>     >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{(x-x_0)(x-x_2)(x-x_3)}{(x_1-x_0)(x_1-x_2)(x_1-x_3)}">  
>     >    
>     >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{(x-0)(x-5)(x-7)}{(2-0)(2-5)(2-7)}">
>     >    
>     >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{x^3-12x^2+35x}{30}">
> 
>   * <img alight ="center" src="https://latex.codecogs.com/svg.latex?\Large&space;L_2(x)"/>
> 
>     >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{(x-x_0)(x-x_1)(x-x_3)}{(x_2-x_0)(x_2-x_1)(x_2-x_3)}">  
>     >    
>     >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{(x-0)(x-2)(x-7)}{(5-0)(5-2)(5-7)}">
>     >    
>     >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{x^3-9x^2+15x}{-30}">
> 
>   * <img alight ="center" src="https://latex.codecogs.com/svg.latex?\Large&space;L_3(x)"/>
> 
>     >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{(x-x_0)(x-x_1)(x-x_2)}{(x_3-x_0)(x_3-x_1)(x_3-x_2)}">  
>     >    
>     >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{(x-0)(x-2)(x-5)}{(7-0)(7-2)(7-5)}">
>     >    
>     >    <img src="https://latex.codecogs.com/svg.latex?\Large&space;=\frac{x^3-7x^2+10x}{70}">
> 
> * Substituindo <img src="https://latex.codecogs.com/svg.latex?\Large&space;L_i(x)"/>
> 
>    <img src="https://latex.codecogs.com/svg.latex?P(x)=1\ast\frac{x^3-14x^2+59x-70}{-70}+5\ast\frac{x^3-12x^2+35x}{30}+266\ast\frac{x^3-9x^2+15x}{-30}+820\ast\frac{x^3-7x^2+10x}{70}"/>
> 
>  <img src="https://latex.codecogs.com/svg.latex?\Large&space;P(x)=3x^3-4x^2-2x+1"/>
