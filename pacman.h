
#define SOBE 'w'
#define DESCE 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define PACMAN 'C'
#define PAREDE_H '-'
#define PAREDE_V '|'
#define VAZIO '.'
#define FANTASMA '@'
#define POCAO 'P'
#define BOMBA 'b'

typedef struct
{
	char** matriz;
	int linha;
	int coluna;
}MAPA;

void limpaMemoria ( MAPA *m );
void leMapa ( MAPA *m );
int perdeu ( MAPA *m );
void movimento ( char direcao, MAPA *m );
void fantasmas( MAPA *m );
void moveFantasmas( MAPA *destino, int x, int y );
void bomba ( MAPA *m );
void mostraMapa ( MAPA *m );
void imprimeparte ( char desenho[4][7], int parte );




