clc
clear
close all
function res = f(x)
  if ~isnumeric(x) error('Number expected','The function expects a number') endif
  tamanho = size(x);
  res = [];
  for i=1:tamanho
     res =[res ~(x<0)];
  end 

endfunction


hold on;
#display(f(0));
x = -5:0.1:5;

y = f(x);
plot(x,y);
grid
xlabel("aa")
ylim([-1 3])
hold off
 
