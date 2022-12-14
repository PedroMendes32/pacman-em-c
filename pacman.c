
#include<stdio.h> 
#include<stdlib.h> 
#include<locale.h>
#include<ctype.h>
#include<time.h>
#include<string.h>
#include"pacman.h"

MAPA m;
int temPocao = 0;
	
int main(void)
{	
	
	setlocale(LC_ALL,"Portuguese");
	
	char jogada;
	
	leMapa(&m);
	
	do
	{	
		
		mostraMapa(&m);
		mostraStatus();
		printf("- Digite a sua jogada: \n");
		fflush(stdin);
		scanf(" %c",&jogada);
		
		if (( jogada == BOMBA && temPocao )|| (jogada == BOMBA2 && temPocao ))
		{
			bomba(&m);
		}
		movimento(jogada,&m);
		fantasmas(&m);
		geraBomba(&m);
		
		system("cls");
	}
	
	while(!resultado(&m));
	
	mostraMapa(&m);
	
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
		printf("\n N?o foi poss?vel ler o mapa!");
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


void limpaMemoria( MAPA *m )
{
	int i;
	for ( i = 0; i < m->linha; i++ )
	{
		free(m->matriz[i]);
	}
	free(m->matriz);
}

int resultado ( MAPA *m )
{	
	int perdeu = 1;
	int temFantasma = 0;

	int i,j;

	for ( i = 0; i < m->linha; i++ )
	{
		for ( j = 0; j < m->coluna; j++ )
		{
			if ( m->matriz[i][j] == PACMAN )
			{
				perdeu = 0;
			}
		}
	}

	if ( perdeu )
	{	
		exibeDerrota();
		return 1;
	}


	for ( i = 0; i < m->linha; i++ )
	{
		for ( j = 0; j < m->coluna; j++ )
		{
			if ( m->matriz[i][j] == FANTASMA )
			{
				temFantasma = 1;
			}
		}
	}
	
	if ( temFantasma == 0 )
	{	
		exibeVitoria();
		return 1;
	}
	
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
	
	if ( direcao != ESQUERDA && direcao != DESCE && direcao != SOBE && direcao != DIREITA)
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
			
			if ( m->matriz[x][y-1] != VAZIO && m->matriz[x][y-1] != POCAO )
			{
				return;
			}
			if ( m->matriz[x][y-1] == POCAO )
			{
				temPocao = 1;
			}
			m->matriz[x][y - 1] = PACMAN;
			break;
		
        case DIREITA:
        	
        	if ( m->matriz[x][y+1] != VAZIO && m->matriz[x][y+1] != POCAO )
			{
				return;
			}
        	if ( m->matriz[x][y+1] == POCAO )
			{
				temPocao = 1;
			}
   			m->matriz[x][y + 1] = PACMAN;
   			break;
   		
   		case SOBE:
   			
   			if ( m->matriz[x-1][y] != VAZIO && m->matriz[x-1][y] != POCAO )
			{
				return;
			}
			if ( m->matriz[x-1][y] == POCAO )
			{
				temPocao = 1;
			}
			   
   			m->matriz[x-1][y] = PACMAN;
   			break;
   		
   		case DESCE:
   			
   			if ( m->matriz[x+1][y] != VAZIO && m->matriz[x+1][y] != POCAO )
			{
				return;
			}
			if ( m->matriz[x+1][y] == POCAO )
			{
				temPocao = 1;
			}
   			m->matriz[x+1][y] = PACMAN;
   			break;
	}
	
	m->matriz[x][y] = VAZIO;
	
	
}

void fantasmas( MAPA *m )
{
	char matriz[m->linha][m->coluna];
	int i,j;
	
	for ( i = 0; i < m->linha; i++ )
	{
		for ( j = 0; j < m->coluna; j++ )
		{
			matriz[i][j] = m->matriz[i][j];
		}
	}

	for ( i = 0; i < m->linha; i++ )
	{
		for ( j = 0; j < m->coluna; j++ )
		{
			if ( matriz[i][j] == FANTASMA )
			{
				moveFantasmas(m,i,j);
			}
		}
	}
}

void moveFantasmas ( MAPA *destino, int x, int y )
{
	srand(time(NULL));

	int podeMover = 0;
	int jogada;

	while ( !podeMover )
	{
		jogada = rand() % 4;

		switch ( jogada )
		{
			case 0:
				
				if ( destino->matriz[x][y+1] != VAZIO && destino->matriz[x][y+1] != PACMAN )
				{
					break;
				}
				destino->matriz[x][y+1] = FANTASMA;
				podeMover = 1;
				break;

			case 1:

				if ( destino->matriz[x][y-1] != VAZIO && destino->matriz[x][y-1] != PACMAN )
				{
					break;
				}
				destino->matriz[x][y-1] = FANTASMA;
				podeMover = 1;
				break;
			
			case 2:

				if ( destino->matriz[x+1][y] != VAZIO && destino->matriz[x+1][y] != PACMAN )
				{
					break;
				}
				destino->matriz[x+1][y] = FANTASMA;
				podeMover = 1;
				break;

			case 3:

				if ( destino->matriz[x-1][y] != VAZIO && destino->matriz[x-1][y] != PACMAN )
				{
					break;
				}
				destino->matriz[x-1][y] = FANTASMA;
				podeMover = 1;
				break;
		}
	}

	destino->matriz[x][y] = VAZIO;
}

void bomba ( MAPA *m )
{	
	temPocao = 0;
	int i,j;
	int x,y;
	
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
	
	for ( i = 1; i <= 3; i++ )
	{
		if ( m->matriz[x][y+i] == VAZIO || m->matriz[x][y+i] == FANTASMA )
		{
			m->matriz[x][y+i] = VAZIO;
		}
		else
		{
			break;
		}
	}
	
	for ( i = 1; i <= 3; i++ )
	{
		if ( m->matriz[x][y-i] == VAZIO || m->matriz[x][y-i] == FANTASMA )
		{
			m->matriz[x][y-i] = VAZIO;
		}
		else
		{
			break;
		}
	}
	
	for ( i = 1; i <= 3; i++ )
	{
		if ( m->matriz[x+i][y] == VAZIO || m->matriz[x+i][y] == FANTASMA )
		{
			m->matriz[x+i][y] = VAZIO;
		}
		else
		{
			break;
		}
	}
	
	for ( i = 1; i <= 3; i++ )
	{
		if ( m->matriz[x-i][y] == VAZIO || m->matriz[x-i][y] == FANTASMA )
		{
			m->matriz[x-i][y] = VAZIO;
		}
		else
		{
			break;
		}
	}
}

char desenhoFantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenhoParede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoPacman[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhoPocao[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhoVazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void imprimeparte ( char desenho[4][7], int parte )
{
	printf("%s",desenho[parte]);
}

void mostraMapa ( MAPA *m )
{
	int i,j;
	int parte;
	
	for ( i = 0; i < m->linha; i++ )
	{
		for ( parte = 0; parte < 4; parte++ )
		{
			for ( j = 0; j < m->coluna; j++ )
			{
				switch ( m->matriz[i][j] )
				{
					case FANTASMA:
						imprimeparte(desenhoFantasma,parte);
						break;
					
					case PACMAN:
						imprimeparte(desenhoPacman,parte);
						break;
					
					case VAZIO:
						imprimeparte(desenhoVazio,parte);
						break;
					
					case POCAO:
						imprimeparte(desenhoPocao,parte);
						break;
					
					case PAREDE_H:
					case PAREDE_V:
						imprimeparte(desenhoParede,parte);
						break;
				}
			}
			printf("\n");
		}
	}
}

void mostraStatus ( void )
{
	printf("\t\t\t TEM BOMBA: %s\n\n", temPocao ? "SIM":"N?O");
}

void geraBomba(MAPA *m)
{
	int i,j;
	int existe = 0;
	int podeCriar = 0;
	int x,y;
	
	for ( i = 0; i < m->linha; i++ )
	{
		for ( j = 0; j < m->coluna; j++ )
		{
			if ( m->matriz[i][j] == POCAO )
			{
				existe = 1;
				return;
			}
		}
	}
	
	if ( !existe )
	{
		while ( !podeCriar )
		{
			x = rand() % m->linha;
			y = rand() % m->coluna;
			
			if ( m->matriz[x][y] == VAZIO )
			{
				m->matriz[x][y] = POCAO;
				podeCriar = 1;
			}
		}
	}
}

void exibeVitoria(void)
{	
	
	printf("       ___________      \n");
	printf("      '._==_==_=_.'     \n");
	printf("      .-\\:      /-.    \n");
	printf("     | (|:.     |) |    \n");
	printf("      '-|:.     |-'     \n");
	printf("        \\::.    /      \n");
	printf("         '::. .'        \n");
	printf("           ) (          \n");
	printf("         _.' '._        \n");
	printf("        '-------'       \n\n");
	printf("\n\n\n");
	printf("-------- VOC? VENCEU! --------");
	printf("\n\n\n");
	
	
}

void exibeDerrota (void)
{
	
	printf("    _______________         \n");
	printf("   /               \\       \n"); 
	printf("  /                 \\      \n");
	printf("//                   \\/\\  \n");
	printf("\\|   XXXX     XXXX   | /   \n");
	printf(" |   XXXX     XXXX   |/     \n");
	printf(" |   XXX       XXX   |      \n");
	printf(" |                   |      \n");
	printf(" \\__      XXX      __/     \n");
	printf("   |\\     XXX     /|       \n");
	printf("   | |           | |        \n");
	printf("   | I I I I I I I |        \n");
	printf("   |  I I I I I I  |        \n");
	printf("   \\_             _/       \n");
	printf("     \\_         _/         \n");
	printf("       \\_______/           \n");
	printf("\n\n\n");
	printf("-------- VOC? PERDEU! --------");
	printf("\n\n\n");
	
}










