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
void movimento ( char direcao );

