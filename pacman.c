#include<stdio.h> 
#include<stdlib.h> 
#include<locale.h>
#include<ctype.h>
#include"pacman.h"

MAPA m;

int main(void)
{	
	char jogada;
	
	leMapa(&m);
	
	do
	{
		mostraMapa(&m);
		printf("- Digite a sua jogada: \n");
		scanf(" %c",&jogada);
		
		movimento(jogada,&m);
	}
	
	while(!perdeu());
	
	limpaMemoria(&m);
	
	printf("\n\n\n");
	system("pause");
	
	return 0;
}

void leMapa ( MAPA *m )
{
	FILE *arquivo;
	int i;
	
	if (( arquivo = fopen("mapa.txt","r") ) == NULL )
	{
		printf("\n Não foi possível ler o mapa!");
		exit(1);
	}
	
	fscanf(arquivo,"%d %d",&(m->linha),&(m->coluna));
	
	m->matriz = malloc( sizeof(char*) * m->linha );
	for ( i = 0; i < m->linha; i++ )
	{
		m->matriz[i] = malloc ( sizeof(char) * (m->coluna+1) );
	}
	
	for ( i = 0; i < m->linha; i++ )
	{
		fscanf(arquivo,"%s",m->matriz[i]);
	}
}

void mostraMapa ( MAPA *m )
{
	int i;
	
	for ( i = 0; i < m->linha; i++ )
	{
		printf("\n%s",m->matriz[i]);
	}
}

void limpaMemoria( MAPA *m )
{
	int i;
	for ( i = 0; i < m->linha; i++ )
	{
		free(m->matriz[i]);
	}
	free(m->matriz);
}

int perdeu ( void )
{
	return 0;
}

void movimento( char direcao, MAPA *m )
{
	int x,y;
	int i,j;
	
	if ( isupper(direcao) )
	{
		direcao = tolower(direcao);
	}
	
	if ( direcao != ESQUERDA && direcao != DESCE && direcao != SOBE && direcao != DIREITA )
	{
		return;
	}
	
	for ( i = 0; i < m->linha; i++ )
	{
		for ( j = 0; j < m->coluna; j++ )
		{
			if ( m->matriz[i][j] == PACMAN )
			{
				x = i;
				y = j;
			}
		}
	}
	
	switch ( direcao )
	{	
		case ESQUERDA:
			
			if ( m->matriz[x][y-1] != VAZIO )
			{
				return;
			}
			
			m->matriz[x][y - 1] = PACMAN;
			break;
		
        case DIREITA:
        	
        	if ( m->matriz[x][y+1] != VAZIO )
			{
				return;
			}
        	
   			m->matriz[x][y + 1] = PACMAN;
   			break;
   		
   		case SOBE:
   			
   			if ( m->matriz[x-1][y] != VAZIO )
			{
				return;
			}
			   
   			m->matriz[x-1][y] = PACMAN;
   			break;
   		
   		case DESCE:
   			
   			if ( m->matriz[x+1][y] != VAZIO )
			{
				return;
			}
   			
   			m->matriz[x+1][y] = PACMAN;
   			break;
	}
	
	m->matriz[x][y] = VAZIO;
}