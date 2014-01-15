#ifndef funcoes_h
#define funcoes_h

#include "estruturas.h"
#include "arquivo.h"

void inicializar_allegro(int);
void cont_fps();
void desenha_sprite(BITMAP*, BITMAP*, BITMAP*, int);
BITMAP *desenha_mapa(MAPA, BITMAP*, int, int);
BITMAP *desenha_constr_menu(BITMAP*, CONSTR_MENU);
char *retorna_nome_arq_imagem (int);
MAPA zerar_matriz_mapa(MAPA);
MAPA define_mapa_padrao();
MAPA define_mapa();
int deseja_salvar();
CONSTR_MENU define_menu(CONSTR_MENU);
void limpa_buffer(BITMAP*, int, int);
JOGADOR fcair(JOGADOR, int);
JOGADOR fpular(JOGADOR, int);
JOGADOR marretar(JOGADOR, MAPA, BITMAP*, BITMAP*, BITMAP*, int);
JOGADOR marretando(JOGADOR, MAPA*, BITMAP*, BITMAP*, BITMAP*, int);
JOGADOR anda_direita(JOGADOR, BITMAP**, BITMAP**, MAPA, int*, int*, int);
JOGADOR anda_esquerda(JOGADOR, MAPA, int);
COBRINHA movimenta_cobrinha(COBRINHA, MAPA, JOGADOR);
void desenha_buffer(BITMAP*, BITMAP*, int, int);
COBRINHA inicializa_cobrinha(COBRINHA, int, int, int);
JOGADOR inicializa_jogador(JOGADOR, int, int, int, int);
void pegar_broas(JOGADOR*, MAPA*, BITMAP*);
void inicializar_jogo (JOGADOR*, COBRINHA*, int);

#endif
