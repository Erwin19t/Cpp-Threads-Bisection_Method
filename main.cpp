#include <mutex>
#include <iostream>
#include <thread>
#include <math.h>

using namespace std;

double Evaluar(double x)
{
	//Funcion a evaluar: f(x) = x⁷ - 2x⁵ + 4x⁴ - 3x² -1
	return pow(x,7) - 2*pow(x,5) + 4*pow(x,4) - 3*pow(x,2) - 1;
}

double Biseccion(double a, double b, mutex *m)
{
	int Counter = 0;
	double a_aux, b_aux, AB;//Variables auxiliares
	double Fa, Fb, Fab;	//Funcion evaluada n diferentes puntos
	double Fab_ant = 0.0;
	double Error = 100.0;	//Error = Fab_k - Fab_(k-1)
	a_aux = a;		//variable auxiliar
	b_aux = b;		//Variable auxiliar
	
	while(Error > (1*pow(10,-9)))
	{
		//Encontramos punto medio (Raiz aproximada)
		AB  = (a_aux + b_aux)/2;	
		//Evaluamos la funcion en A
		Fa  = pow(a_aux,7) - 2*pow(a_aux,5) + 4*pow(a_aux,4) - 3*pow(a_aux,2) - 1;
		//Evaluamos la funcion en B
		Fb  = pow(b_aux,7) - 2*pow(b_aux,5) + 4*pow(b_aux,4) - 3*pow(b_aux,2) - 1;
		//Evaluamos la funcion en pto medio
		Fab = pow(AB,7) - 2*pow(AB,5) + 4*pow(AB,4) - 3*pow(AB,2) - 1;
	
		//Condiciones para cambiar los pts A y B
		if((Fa * Fab) < 0)
		{
			b_aux = AB;
		}
		if((Fb * Fab) < 0)
		{
			a_aux = AB;
		}
		//Calculo de error
		Error = abs(Fab - Fab_ant);
		//Actualizamos la raiz anteriror
		Fab_ant = Fab;		
		//Incrementamos el contador al final de cada iteracion
		Counter++;
	}
	
	m->lock();
	cout<<"La raiz estimada es:"<<AB<<endl;
	cout<<"Se encontro la solucion en la iteracion "<<Counter<<endl<<endl;
	m->unlock();
	return AB;
}

int main()
{
	mutex m;
	
	thread t1(Biseccion, -2.0, -1.85, &m);
	thread t2(Biseccion, -2.0, -1.85, &m);
	thread t3(Biseccion, -1.5, -0.9, &m);
	thread t4(Biseccion, -1.5, -0.9, &m);
   	thread t5(Biseccion, 1.0, 1.5, &m);				
	thread t6(Biseccion, 1.0, 1.5, &m);	
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	
	return 0;
}
