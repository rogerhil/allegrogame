#ifndef estruturas_h
#define estruturas_h

#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include <math.h>

typedef struct MAPA{   
    int largura; 
    int altura;
    int matriz[24][32*10];
    BITMAP *spr;
} MAPA;


typedef struct COORD{
    int x;
    int y;
    int xm;
    int ym;
    int px;
    int py;
} COORD;

typedef struct OMC{
    int mi0;
    int mi1;
    int mim;
    
    int mj0;
    int mj1;
    int mjm;
    
    int mmj0;
    int mmj1;
    int mmjm;
} OMC;

typedef struct MPOS{
    int i;
    int j;
} MPOS;


typedef struct JOGADOR{
    BITMAP **bmp_mov;
    BITMAP **bmp_marreta;
    BITMAP *bmp_padrao;
    BITMAP *bmp;
    BITMAP *buffer;
    int fst;
    int esq_dir;
    int marretando;
    int tempo;
    COORD coord;
    OMC omc;
    int vpulo;
    int comeca_cair;
    int comeca_pular;
    int para_pular;
    int vidas;
    int broas;
} JOGADOR;

typedef struct COBRINHA{
    BITMAP **bmp_mov;
    BITMAP *bmp_padrao;
    BITMAP *bmp;
    BITMAP *buffer;
    int esq_dir;
    int tempo;
    int vpulo;
    COORD coord;
    MPOS mpos;
} COBRINHA;

typedef struct CONSTR_MENU{   
    int objs[32];
} CONSTR_MENU;

#define res_larg   640
#define res_alt    480

#endif
