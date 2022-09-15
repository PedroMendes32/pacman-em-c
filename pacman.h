#define SOBE 'w'
#define DESCE 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define PACMAN 'C'
#define PAREDE_H '-'
#define PAREDE_V '|'
#define VAZIO '.'

typedef struct
{
	char** matriz;
	int linha;
	int coluna;
}MAPA;

void limpaMemoria ( MAPA *m );
void leMapa ( MAPA *m );
void mostraMapa ( MAPA *m );
int perdeu (void);
void movimento ( char direcao, MAPA *m );

