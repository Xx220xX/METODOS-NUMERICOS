from cmath import *
def simpson(a,b,f, N =10000):
	fator = 1
	if b<a:
		a,b=b,a
		fator = -fator
	passo_h = (b-a)/N
	fator = fator*passo_h/3
	result = f(a)+f(b)
	for i in range(1,N):
		if  i%2==0:
			result += 2*f(a+passo_h*i)
		else:
			result += 4*f(a+passo_h*i)
	return result*fator
fatorial =[1,1]
def fat(x):
	t=1
	while x>0:
		t*=x
		x-=1
	return t
def derivada(n,a,f,raio=10,particoes=10000):
	i =1j
	raio=n
	def g(o):
		return f(raio*exp(o*i)+a)*exp(-i*o*n)
	return (simpson(0,2*pi,g,particoes)*fat(n)/\
					(2*pi*raio**n)).real
	
def df(f):
	h=0.00001
	def g(x):
		return (f(x+h)-f(x-h))/(2*h)
	return g
def dfn(f,n):
	if n==0:
		return f
	return dfn(df(f),n-1)
def iAbs(x):
	return x<0 and -x or x
def round(x,dec=4):
	#-0.99999
	i=int(x)#0
	f =x-i#-0.99999
	f*=10**dec#-9999
	if iAbs(f-int(f))<0.5:
		f=int(f)
	elif f>0:
		f=int(f)+1
	else:
		f= int(f)-1
	f/=10**dec
	return i+f


f = lambda x: sin(x)
a=0

i=1

file  = open("result.txt","w")

import sys
orig_stdout = sys.stdout
sys.stdout = file

print("f = sen(x)")

while i<=100:
	dife = round(derivada(i,a,f))
	print("derivada %2d%c n ponto  %g  =     % 5g"%(i,186,a,dife))
	orig_stdout.write("%d\n"%i)
	i+=1

file.close()
