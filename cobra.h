#ifndef cobra_h
#define cobra_h


void cabecario(int score, char *nick);
int movimentacao(int direcao);
void geraCobra(int LadoX, int LadoY);
void corpoCobra(int contador, int *corpoX, int *corpoY);
void novaCabeca(int direcao, int contador, int *corpoX, int *corpoY, int LadoX, int LadoY);


#endif
