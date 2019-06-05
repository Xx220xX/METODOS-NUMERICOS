##fourier
clear;
clc;

e = exp(1);
function  y = sen(x) y = sin(x); endfunction

str =input ("insira a equacao do an: ","s") ;
str = ['@(x,n)' str]; 
funcAn= str2func(str);#criando funcao do an

str = input ("insira a equacao do A0: ","s");
str = ['@(x,n)' str]; 
a0 = str2func(str);
a0 = a0();

anParticular = input("Digite os N(s) em que An é particular: ");
%if anParticular 

%funcBn = 




##function r = an(x,n_max) #an para vetores
##  if ~isnumeric(x) error('Number expected','The function expects a number') endif
##    tamanho = size(x);
##    res = [];
##    for i=1:tamanho
##      resParc = 0 ; 
##      for j =1:n_max
##        resParc = resParc + funcAn(x,j);
##      end
##      res =[res resParc];
##    end 
##  endfunction
##%disp(an(pi,1));