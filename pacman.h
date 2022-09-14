void limpaMemoria ( void );
void leMapa ( void );
void mostraMapa ( void );
int perdeu (void);
void movimento ( char direcao );

typedef struct
{
	char** matriz;
	int linha;
	int coluna;
}MAPA;