#include<stdio.h> 
#include<stdlib.h> 
#include<locale.h>
#include"pacman.h" 

MAPA m;

int main(void)
{	
	char jogada;
	
	leMapa();
	
	do
	{
		mostraMapa();
		printf("- Digite a sua jogada: \n");
		scanf(" %c",&jogada);
		
		movimento(jogada);
	}
	
	while(!perdeu());
	
	limpaMemoria();
	
	printf("\n\n\n");
	system("pause");
	
	return 0;
}

void leMapa ( void )
{
	FILE *arquivo;
	int i;
	
	if (( arquivo = fopen("mapa.txt","r") ) == NULL )
	{
		printf("\n Não foi possível ler o mapa!");
		exit(1);
	}
	
	fscanf(arquivo,"%d %d",&(m.linha),&(m.coluna));
	
	m.matriz = malloc( sizeof(char*) * m.linha );
	for ( i = 0; i < m.linha; i++ )
	{
		m.matriz[i] = malloc ( sizeof(char) * (m.coluna+1) );
	}
	
	for ( i = 0; i < m.linha; i++ )
	{
		fscanf(arquivo,"%s",m.matriz[i]);
	}
}

void mostraMapa ( void )
{
	int i;
	
	for ( i = 0; i < m.linha; i++ )
	{
		printf("\n%s",m.matriz[i]);
	}
}

void limpaMemoria( void )
{
	int i;
	for ( i = 0; i < m.linha; i++ )
	{
		free(m.matriz[i]);
	}
	free(m.matriz);
}

int perdeu ( void )
{
	return 0;
}

void movimento( char direcao )
{
	int x,y;
	int i,j;
	
	for ( i = 0; i < m.linha; i++ )
	{
		for ( j = 0; j < m.coluna; j++ )
		{
			if ( m.matriz[i][j] == '@' )
			{
				x = i;
				y = j;
			}
		}
	}
	
	switch ( direcao )
	{	
		case 'A':
		case 'a':
			m.matriz[x][y - 1] = '@';
			break;
		
		case 'D':
        case 'd':
   			m.matriz[x][y + 1] = '@';
   			break;
   		
   		case 'W':
   		case 'w':
   			m.matriz[x-1][y] = '@';
   			break;
   		
   		case 'S':
   		case 's':
   			m.matriz[x+1][y] = '@';
   			break;
	}
	
	m.matriz[x][y] = '.';
}