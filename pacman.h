#define SOBE 'w'
#define DESCE 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define PACMAN 'C'
#define PAREDE_H '-'
#define PAREDE_V '|'
#define VAZIO '.'
#define FANTASMA '@'

typedef struct
{
	char** matriz;
	int linha;
	int coluna;
}MAPA;

void limpaMemoria ( MAPA *m );
void leMapa ( MAPA *m );
void mostraMapa ( MAPA *m );
int perdeu ( MAPA *m );
void movimento ( char direcao, MAPA *m );
void achaFantasma ( void );
void moveFantasma ( MAPA *m, int xF, int yF );




