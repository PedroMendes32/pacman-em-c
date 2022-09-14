#include<stdio.h> 
#include<stdlib.h> 
#include<locale.h>
#include"pacman.h" 

char** mapa;
int linhas;
int colunas;

int main(void)
{
	leMapa();
	mostraMapa();
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
	
	fscanf(arquivo,"%d %d",&linhas,&colunas);
	
	mapa = malloc( sizeof(char*) * linhas );
	for ( i = 0; i < linhas; i++ )
	{
		mapa[i] = malloc ( sizeof(char) * (colunas+1) );
	}
	
	for ( i = 0; i < linhas; i++ )
	{
		fscanf(arquivo,"%s",mapa[i]);
	}
}

void mostraMapa ( void )
{
	int i;
	
	for ( i = 0; i < linhas; i++ )
	{
		printf("\n%s",mapa[i]);
	}
}

void limpaMemoria( void )
{
	int i;
	for ( i = 0; i < linhas; i++ )
	{
		free(mapa[i]);
	}
	free(mapa);
} 