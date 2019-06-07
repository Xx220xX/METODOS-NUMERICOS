##fourier
clear;
clc;

e = exp(1);

function  y = sen(x) y = sin(x); endfunction
function y = p(n) y = -1; if mod(n,2) == 0 y = 1;endif endfunction
    function y = u(x) 
    y = [];
    tamanho = length(x);
    for i=1:tamanho
      y = [y x(i)>=0];
    end
  endfunction
  
  fprintf(" segue as seguintes convencoes\n      e = %.8f\n      pi = %.8f\n      u(x) = 0, se x<0 ou 1 x >= 0 (degrau unitario)\n",e,pi);
  str = input ("insira a funcao f(x) periodica: ","s") ;
  L = input("digite L (metade do periodo): ");
  str = ['@(x)' str]; 
   titulo = str;
  funcaoAnalitica= str2func(str);#criando funcao de f(x)
  
   str = input ("insira a equacao do A0: ","s"); #inserindo  A0
  str = ['@()' str]; 
  a0 = str2func(str);
  a0 = a0();
  #An_s
  str =input ("insira a equacao do an: ","s") ;
  str = ['@(n)' str]; 
  funcAn= str2func(str);#criando funcao do an
  
 
  
  anParticular = input("Digite os N(s) em que An é particular: ");#casos particulares de an
  anParticAnsw = [];
  
  for i=1:length(anParticular)
    fprintf("digite o A[%d]",anParticular(i));
    str = input(":","s");
    str = ['@()' str];
    ak = str2func(str);
    ak = ak();
    anParticAnsw= [anParticAnsw ak];
  end
  
  
  # BN_s
  str =input ("insira a equacao do bn: ","s") ;
  str = ['@(n)' str]; 
  funcBn = str2func(str);#criando funcao do Bn
  
  bnParticular = input("Digite os N(s) em que Bn é particular: ");#casos particulares de Bn
  bnParticAnsw = [];
  for i=1:length(bnParticular)
    fprintf("digite o B[%d]",bnParticular(i));
    str = input(":","s");
    str = ['@()' str];
    bk = str2func(str);
    bk = bk();
    bnParticAnsw= [bnParticAnsw bk];
  end
  
  
  
  function y = contains(X,element)
    tamanho = length(X);
    for i =1:tamanho
      if element(1) == X(i) y = i; return; endif
      end
      y = 0;
    endfunction
    
    function y = An(n,anP,anPanws,funcAn)
      especial = contains(anP,n);
      if especial~=0 
        y = anPanws(especial);
      else 
        y = funcAn(n);
      end
    endfunction 
    function y = Bn(n,bnP,bnPansw,funcBn)
      especial = contains(bnP,n);
      if especial~=0 
        y = bnPansw(especial);
      else 
        y = funcBn(n);
      endif
    endfunction 
    
    n_max = input("digite N maximo para a serie truncada: ");
    Termos.a0 =a0;
    Termos.anParticular = anParticular;
    Termos.anParticAnsw = anParticAnsw;
    Termos.bnParticular = bnParticular;
    Termos.bnParticAnsw = bnParticAnsw;
    Termos.funcAn = funcAn;
    Termos.funcBn = funcBn;
    
    function y = fourier(x,L,n_max,termos)
      k = length(x);
      y = [];
      resp = 0;
      var_x =0;
      a_n = 0;
      
      for j = 1:k
        var_x = x(j);
        resp =  termos.a0/2;
        for i=1:1:n_max
          a_n = An(i,termos.anParticular,termos.anParticAnsw,termos.funcAn);
          b_n = Bn(i,termos.bnParticular,termos.bnParticAnsw,termos.funcBn);
          resp = resp + a_n*cos(i*pi*var_x/L);
          resp = resp + b_n*sin(i*pi*var_x/L);
        end
        y=[y resp];
      end
    endfunction
    
    function y = fourierOTM(X,L,n_max,termos,an,bn)
      k = length(X);
      y = [];
      resp = 0;
      var_x =0;
      a_n = 0;
      bar_max = 1/k;
      bar_at = 0;
       wwait =  waitbar(bar_at,sprintf("pfv espere calculando pontos para plotar"));
      for j = 1:k
        waitbar(bar_at,wwait);
        var_x = X(j);
        resp =  termos.a0/2;
        for i=1:1:n_max
          a_n = an(i);
          b_n = bn(i);
           resp = resp + a_n*cos(i*pi*var_x/L);
          resp = resp + b_n*sin(i*pi*var_x/L);
        end
        bar_at = j*bar_max;
        y=[y resp];
      end
      close(wwait);
    endfunction
    
    function y = Finit(x,funcx)
      y = [];
      tamanho = length(x);
      for i=1:tamanho
        y = [y funcx(x(i))];
      end
    endfunction
    
    %%% end logic code.
    
    
    x = -L:0.001:L;
    yf = Finit(x,funcaoAnalitica);
    xlabel('x');
    ylabel('u(x)');
    %   y = fourier(x,L,n_max,Termos);
    % cd 'C:\\Users\\Lace\\Desktop\\Henrique\\graficos\\';
    
    
    an =[];
    bn = [];
     bar_max = 1/n_max;
      bar_at = 0;
   wwait =  waitbar(bar_at,sprintf("pfv espere calculando termos an e bn "));
    for n =1:1:n_max
      waitbar(bar_at,wwait);
      bn = [bn Bn(n,Termos.bnParticular,Termos.bnParticAnsw,Termos.funcBn)];
      an = [an An(n,Termos.anParticular,Termos.anParticAnsw,Termos.funcAn)];
      bar_at = bar_at + bar_max;
    end
    close(wwait);
    y = fourierOTM(x,L,n,Termos,an,bn);
    plot(x,y,x,yf);
   
    title(titulo);  
    clear;
    disp('fim');
    %{
    for n = 75:2:400
      y = fourierOTM(x,L,n,Termos,an,bn);
      plot(x,y,x,yf);
      name = sprintf('plot_%d.jpeg',n);
      titulo =sprintf('Fourier  truncada  n = %d',n);
      title(titulo);  
      fprintf("  %d of 1000\n",n);
      print('-dtiff',name);
    end
    
    
    
    %n_max = input("digite N maximo para a serie truncada: ");
    %{
    , xlabel('x'), ylabel('Sin(x)'), title('Sin(x) Graph'),
    grid on, axis equal
    }%
    
    %{
    caso teste
    u(x)
    pi
    1
    0
    []
    (1-(-1)^n)/(n*pi)
    []
    1
    
    u(x)*x
    pi
    pi/2
    ((-1)^n-1)/(n*n*pi)
    []
    -(-1)^n/n
    []
    10
    
    
    u(x)*sen(x)^2
    pi
    1/2
    0
    []
    (2/(pi*n))*((-1)^n-1)/(n^2-4)
    [2]
    0
    10
    
    x+x^2
    1
    2/3
    4*(-1)^n/(n^2*pi^2)
    []
    -2*(-1)^n/(n*pi)
    []
    30
    
    u(x)*sen(x)+u(-x)*cos(x)
    pi
    2/pi
     1/(2*pi)*((1+(-1)^n)/(n+1) + (1+(-1)^n)/(1 - n))
    [1]
    1/2    
     1/(2*pi)*((-1-(-1)^n)/(n+1) + (-1+(-1)^n)/(n -1))
    [1]
    1/2
    10
    
     u(x)*sen(x)+u(-x)*cos(x)
    pi
    2/pi
    (1-p(n))/(pi*(1-n^2))
    [1]
    1/2    
    1/(pi*n)*((p(n+1)-1)/(n+1) + (p(n-1)-1)/(n-1) )
    [1]
    1/2
    130
    
    3 - g
    1+x
    1
    2
    0
    []
    -2*p(n)/(n*pi)
    []
    30
    
    
    
    
    }%
