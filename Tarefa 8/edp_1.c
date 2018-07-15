#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define N 3
#define M1 5
#define h 0.5
#define E 1e-10 // erro considerável

void contorno( double **M )
{	
	int i, j;
	double x = 0, X = 1, y = 0, Y = 2;

	for( i = 0; i < N; i++ )
	{	
		M[i][0] = pow( x, 2);	
		M[i][M1-1] = pow( x-2, 2);
		x += h;
	}

	for( i = 0; i < M1; i++ )
	{	
		M[0][i] = pow( y, 2);	
		M[N-1][i] = pow( y-1, 2);
		y += h;
	}
}


double f()
{	
	return 4;
}

double u( double **M, double **Maux )
{	
	int i, j;
	double eps, a = 0;

	for( i = 1; i < N-1; i++ )
	{	
		for( j = 1; j < M1; j++ )
		{	
			if( Maux[i][j] == 0 )
			{	
				eps = M[i][j];
				M[i][j] = ( M[i-1][j] + M[i+1][j] + M[i][j-1] + M[i][j+1] -pow( h, 2)* f())/ 4.;
				eps = fabs( eps - M[i][j] );
				if( eps > a )
					a = eps;
			}
		}
	}
	return a;	
}

void imprime( double **M, int NL, int NC)
{	
	int i, j;

	//printf("Matriz calculada\n");	
	for(i = 0; i < NL; i++)
	{
		for( j = 0; j < NC; j++)
			printf("%.2lf\t ",M[i][j]);  
		puts("");
	}	
}

void main()
{	
	double	**M, **Maux, erro;
	int  i, j, cont = 0;
 
	Maux = malloc( N* sizeof(double*));
	for( i = 0; i < M1; i++ )
		Maux[i] = malloc( M1* sizeof(double));
		
	M = malloc( N* sizeof(double*));
	for( i = 0; i < M1; i++ )
		M[i] = malloc( M1* sizeof(double));
		
	contorno(M);
	//mascara
	for( i = 0; i < N; i++ )
	{	
		Maux[i][0] = 1;	
		Maux[i][M1-1] = 1;
	}
	for( i = 0; i < M1; i++ )
	{	
		Maux[0][i] = 1;	
		Maux[N-1][i] = 1;
	}	
		
	do
	{	
		erro = u(M, Maux);
		cont++;
	}while( erro > E );
	
	imprime(M,N,M1);
}
