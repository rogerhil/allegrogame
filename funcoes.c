#include "funcoes.h"

int n_mov = 0;

void desenha_sprite(BITMAP *buffer2, BITMAP *dest, BITMAP *orig, int angulo)
{    
    draw_sprite(dest, buffer2, -10, -10);
    rotate_sprite(dest, orig, 0, 0, itofix(angulo));
}

char *retorna_nome_arq_imagem (int v)
{

    char *arquivo_img;
    arquivo_img = malloc (100);
    arquivo_img = strdup ("imagens/estrada.bmp");

    switch (v)
    {
        case 0:
        {
            arquivo_img = strdup("imagens/ceu1.bmp");
            break;
        }
        case 1:
        {
            arquivo_img = strdup("imagens/broa1.bmp");
            break;
        }
        case 50:
        {
            arquivo_img = strdup("imagens/chao1.bmp");
            break;
        }
        case 11:
        {
            arquivo_img = strdup("imagens/muro1.bmp");
            break;
        }
        case 12:
        {
            arquivo_img = strdup("imagens/muro1.bmp");
            break;
        }
        default:
        {
            arquivo_img = strdup("imagens/ceu1.bmp");
        }
    }
    return(arquivo_img);
}

BITMAP *desenha_mapa(MAPA mapa, BITMAP *buffer, int comeco, int fim)
{
    int i, j, x, y;
    BITMAP *spr_img;
    BITMAP *bmp;
    char *arquivo_img;
    arquivo_img = malloc (100);
    arquivo_img = strdup ("imagens/ceu1.bmp");
   
    for (i = 0; i < res_alt / 20; i++)
    {
        for (j = comeco; j < fim; j++)
        {
            arquivo_img = retorna_nome_arq_imagem(mapa.matriz[i][j]);
            spr_img = load_bitmap(arquivo_img, NULL); 
            bmp = create_bitmap(spr_img->w, spr_img->h);
            desenha_sprite(bmp, bmp, spr_img, 0);
            draw_sprite(buffer, bmp, (j-comeco)*20, i*20);
        }
    }
    clear_bitmap(spr_img);
    clear_bitmap(bmp);
    return (buffer);
}

MAPA zerar_matriz_mapa(MAPA mapa)
{
    int i,j;
    
    for (i = 0; i < res_alt / 20; i++)
    {
        for (j = 0; j < (res_larg / 20)*10; j++)
        {
            mapa.matriz[i][j] = 0;
        }
    }
    return mapa;
}

MAPA define_mapa()
{

    MAPA mapa;
    FILE *arquivo;
    int i,j, k, m = -1;
    
    char *ent, *nomearq;
    ent = malloc (10);
    nomearq = malloc (50);
    nomearq = strdup("fases/fase1.cen");
    
    abrir_arquivo(&arquivo, nomearq, LER);
    
    zerar_matriz_mapa(mapa);
    
    ent = strdup("");
    
    for (i = 0; i < res_alt / 20; i++)
    {
        for (j = 0; j < res_larg / 20; j++)
        {
            for (k = 0; k < 3; k++)
            {
                m++;
                fscanf(arquivo, "%c", &ent[k]);
                if (ent[k] == ',')
                {
                    ent[k] = ' ';
                    mapa.matriz[i][j] = atoi(ent);
                    ent = strdup("");
                    break;
                }

            }
        }
        
    }
    
    return mapa;
}

int deseja_salvar()
{
    BITMAP *buf_tras = create_bitmap(400, 30);
    int bool = 1;
    
    blit(screen, buf_tras, 120, 220, 0, 0, 400, 30);
    textprintf(screen, font, 120, 220, makecol(255,255,255), "Tem certeza que deseja salvar e começar o jogo?");
    textprintf(screen, font, 200, 240, makecol(255,255,255), "<SIM>");
    textprintf(screen, font, 360, 240, makecol(255,255,255), "<NAO>");
    //draw_sprite(screen, buf_perg, 120, 220);
    
    while(!key[KEY_ESC])
    {
        if (mouse_y > 235 && mouse_y < 255)
        {
            if (mouse_x > 200 && mouse_x < 230  && mouse_b == 1)
            {
                bool = 1;
                draw_sprite(screen, buf_tras, 120, 220);
                break;
            }

            if (mouse_x > 360 && mouse_x < 390 && mouse_b == 1)
            {
                bool = 0;
                draw_sprite(screen, buf_tras, 120, 220);
                break;
            }            
        }
    }
    
    return bool;    
}

MAPA define_mapa_padrao() 
{    
    MAPA mapa;
    int i,j;
    mapa = zerar_matriz_mapa(mapa);
    
    for (j = 0; j < (res_larg / 20)*10; j++)
    {
        mapa.matriz[11][j] = 50;
        mapa.matriz[10][j] = 50;
        if (j % 8 == 0 || j % 8 == 1  || j % 8 == 2  || j % 8 == 3  || j % 8 == 4  || j % 8 == 5)
            mapa.matriz[9][j] = 50;
    }
    
    for (j = 0; j < (res_larg / 20)*10; j++)
    {
        mapa.matriz[10][j] = 50;
    }
    

    mapa.matriz[7][5] = 11;
    mapa.matriz[7][6] = 12;
    mapa.matriz[7][7] = 11;
    mapa.matriz[7][8] = 12;

    mapa.matriz[4][3] = 1;
    mapa.matriz[4][4] = 1;
    mapa.matriz[3][16] = 1;
    mapa.matriz[3][18] = 1;
    
    mapa.matriz[7][12] = 11;
    mapa.matriz[7][13] = 11;
    
    mapa.matriz[5][15] = 11;
    mapa.matriz[5][16] = 11;
    mapa.matriz[5][17] = 11;
    mapa.matriz[5][18] = 11;
    
    mapa.matriz[9][1] = 11;
    mapa.matriz[8][1] = 11;
    mapa.matriz[7][1] = 11;
    mapa.matriz[6][1] = 11;
    
    mapa.matriz[6][15] = 11;
    mapa.matriz[6][16] = 12;
    mapa.matriz[6][17] = 11;
    mapa.matriz[6][18] = 11;
        
    mapa.matriz[7][21] = 12;
    mapa.matriz[7][22] = 11;
    
    mapa.matriz[8][36] = 11;
    mapa.matriz[8][37] = 12;
    mapa.matriz[8][44] = 11;
    
    mapa.matriz[8][49] = 11;
    mapa.matriz[7][50] = 11;
    mapa.matriz[6][51] = 11;

    mapa.matriz[9][53] = 50;
    mapa.matriz[9][54] = 50;
    mapa.matriz[9][55] = 50;
    mapa.matriz[9][56] = 50;
    mapa.matriz[9][57] = 50;
    mapa.matriz[9][58] = 50;
    mapa.matriz[9][59] = 50;
    
    mapa.matriz[8][54] = 50;
    mapa.matriz[8][55] = 50;
    mapa.matriz[8][56] = 50;
    mapa.matriz[8][57] = 50;
    mapa.matriz[8][58] = 50;

    mapa.matriz[7][55] = 50;
    mapa.matriz[7][56] = 50;
    mapa.matriz[7][57] = 50;

    mapa.matriz[6][56] = 12;
        
    mapa.matriz[8][60] = 11;
    mapa.matriz[9][60] = 11;
    mapa.matriz[10][60] = 11;

    
    for (j = 0; j < 10; j++)
    {    
        mapa.matriz[j][120] = 50;
        mapa.matriz[j][121] = 50;
        mapa.matriz[j][122] = 50;
    }
    return mapa;
}

void limpa_buffer(BITMAP *buf, int px, int py)
{
    draw_sprite(screen, buf, px, py);
}

void desenha_buffer(BITMAP *buffer, BITMAP *bmp, int px, int py)
{
    blit(screen, buffer, px, py, 0, 0, px + 20, py + 20);
    draw_sprite(screen, bmp, px, py);
}

JOGADOR fcair(JOGADOR jogador, int local)
{
    int inty;
    if (jogador.comeca_cair)
    {
        jogador.tempo = 0;
        jogador.comeca_cair = 0;
    }
    if (local < 10)
    {
        jogador.tempo++;
        jogador.coord.y += jogador.tempo*jogador.tempo/jogador.vpulo;
        jogador.para_pular = 1;
    }
    else
    {
        inty = jogador.coord.y / 20; 
        jogador.coord.y = jogador.coord.y - (jogador.coord.y - inty*20);
        jogador.tempo = 0;
        jogador.comeca_cair = 1;
        jogador.comeca_pular = 1;
        jogador.para_pular = 0;
    }
    return jogador;
}
JOGADOR fpular(JOGADOR jogador, int local)
{
    double d;
    
    if (jogador.comeca_pular)
    {
        jogador.tempo = -30;
    }
    
    d = 2 * ((double)jogador.tempo / jogador.vpulo);
    
    if ((d != 0) & (local < 10))
    {
        
        jogador.tempo++;
        jogador.comeca_pular = 0;
        jogador.coord.y -= jogador.tempo*jogador.tempo/jogador.vpulo;
    }
    else
    {
        jogador.para_pular = 1;
        jogador.tempo = 0;
    }
    
    return jogador;
}

JOGADOR marretar(JOGADOR jogador, MAPA mapa, BITMAP *bmp_muro_quebrado, BITMAP *bmp_ceu, BITMAP *bmp_broa, int p)
{
    int mjff;
    
    if (jogador.esq_dir)
        jogador.bmp = jogador.bmp_marreta[0];
    else
        jogador.bmp = jogador.bmp_marreta[2];
    
    mjff = (jogador.coord.xm + 10 - p) / 20;
    if (mapa.matriz[jogador.omc.mi1][mjff] == 11)
    {
        draw_sprite(screen, bmp_muro_quebrado, jogador.omc.mjm*20 - p, jogador.omc.mi1*20);
    }
    if (mapa.matriz[jogador.omc.mi1][mjff] == 12)
    {
        draw_sprite(screen, bmp_ceu, jogador.omc.mjm*20 - p, jogador.omc.mi1*20);
        draw_sprite(screen, bmp_broa, jogador.omc.mjm*20 - p, jogador.omc.mi1*20);
    }                
    jogador.marretando = 1;
    
    return jogador;
}

JOGADOR marretando(JOGADOR jogador, MAPA *mapa, BITMAP *bmp_muro_quebrado, BITMAP *bmp_ceu, BITMAP *bmp_broa, int p)
{
    int mjff;

    if (jogador.esq_dir)
        jogador.bmp = jogador.bmp_marreta[1];
    else
        jogador.bmp = jogador.bmp_marreta[3];
    jogador.marretando = 0;
    mjff = (jogador.coord.xm + 10 - p) / 20;
    if (mapa->matriz[jogador.omc.mi1][mjff] == 11)
    {
        mapa->matriz[jogador.omc.mi1][mjff] = 0;
        draw_sprite(screen, bmp_ceu, jogador.omc.mjm*20 - p, jogador.omc.mi1*20);
    }
    if (mapa->matriz[jogador.omc.mi1][mjff] == 12)
    {
        mapa->matriz[jogador.omc.mi1][mjff] = 1;
        //draw_sprite(screen, bmp_ceu, jogador.omc.mjm*20 - p, jogador.omc.mi1*20);
    }
    return jogador;
}

JOGADOR anda_direita(JOGADOR jogador, BITMAP **main_buffer, BITMAP **prox_buffer, MAPA mapa, int *p, int *passo, int velocidade)
{
    jogador.esq_dir = 1;
    if (mapa.matriz[jogador.omc.mi1-1][jogador.omc.mmj1] < 10)
    {
        jogador.coord.xm += velocidade;
        jogador.coord.x += velocidade;
        
    }
    
    switch ((n_mov/10) % 3)
    {
        case 0:
        {
            jogador.bmp = jogador.bmp_mov[0];
            break;
        }
        case 1:
        {
            jogador.bmp = jogador.bmp_mov[1];
            break;
        }
        case 2:
        {
            jogador.bmp = jogador.bmp_mov[2];
            break;
        }
        default:
        {
            jogador.bmp = jogador.bmp_padrao;
        }
    }
    
    n_mov++;
    if (n_mov > 99999)
        n_mov = 0;


    if (((jogador.coord.x) >= res_larg / 2) & ((jogador.coord.x) <= res_larg / 2 + 20))
    {
        *p += 2 * velocidade;
        jogador.fst = 1;
        jogador.coord.x -= 2 * velocidade;

        blit(screen, *main_buffer, 0, 0, 0, 0, res_larg, res_alt);
        blit(*main_buffer, *main_buffer, 2 * velocidade, 0, 0, 0, res_larg, res_alt);
        blit(*prox_buffer, *main_buffer, 0, 0, res_larg - *p, 0, 20, res_alt);
        draw_sprite(screen, *main_buffer, 0, 0);
        
       
        if (*p == 20)
        {
            *passo += 1;
            *prox_buffer = desenha_mapa(mapa, *prox_buffer, (res_larg / 20) + *passo, (res_larg / 20) + 1 + *passo);
            *p = 0;
        }
        
    }

    return jogador;
}

JOGADOR anda_esquerda(JOGADOR jogador, MAPA mapa, int velocidade)
{
    jogador.esq_dir = 0;
    if (mapa.matriz[jogador.omc.mi1-1][jogador.omc.mmj1-1] < 10)
    {
        jogador.coord.x -= velocidade;
        jogador.coord.xm -= velocidade;
    }
    
    switch ((n_mov/10) % 3)
    {
        case 0:
        {
            jogador.bmp = jogador.bmp_mov[3];
            break;
        }
        case 1:
        {
            jogador.bmp = jogador.bmp_mov[4];
            break;
        }
        case 2:
        {
            jogador.bmp = jogador.bmp_mov[5];
            break;
        }
        default:
        {
            jogador.bmp = jogador.bmp_padrao;
        }
    }
    
    n_mov++;
    if (n_mov > 99999)
        n_mov = 0;

    return jogador;
}

COBRINHA movimenta_cobrinha(COBRINHA cobrinha, MAPA mapa, JOGADOR jogador)
{

    int inty;

    if (cobrinha.coord.xm < jogador.coord.xm + res_larg / 2 + 40)
    {
        if (cobrinha.coord.xm > -20 || cobrinha.coord.xm < 300)
        {
            if (cobrinha.esq_dir == 0)
            {
                cobrinha.coord.x--;
                cobrinha.coord.xm--;
                if (mapa.matriz[(cobrinha.coord.y) / 20][(cobrinha.coord.xm) / 20] > 10)
                {
                    cobrinha.esq_dir = 1;
                }
            }
            if (cobrinha.esq_dir == 1)
            {
                cobrinha.coord.x++;
                cobrinha.coord.xm++;
                if (mapa.matriz[(cobrinha.coord.y) / 20][(cobrinha.coord.xm + 20) / 20] > 10)
                {
                    cobrinha.esq_dir = 0;
                }
            }
        }
    
        switch ((cobrinha.coord.x/5) % 2)
        {
            case 0:
            {
                if (cobrinha.esq_dir)
                {
                    cobrinha.bmp = cobrinha.bmp_mov[0];
                }
                else
                {
                    cobrinha.bmp = cobrinha.bmp_mov[2];
                }
                break;
            }
            case 1:
            {
                if (cobrinha.esq_dir)
                {
                    cobrinha.bmp = cobrinha.bmp_mov[1];
                }
                else
                {
                    cobrinha.bmp = cobrinha.bmp_mov[3];
                }
                break;
            }
            default:
            {
                cobrinha.bmp = cobrinha.bmp_padrao;
            }
        }
                    
    
        if (mapa.matriz[(cobrinha.coord.y + 20) / 20][cobrinha.coord.xm / 20] < 10)
        {
            cobrinha.tempo++;
            cobrinha.coord.y += cobrinha.tempo * cobrinha.tempo/cobrinha.vpulo;
        }
        else
        {
            inty = cobrinha.coord.y / 20;
            cobrinha.coord.y = cobrinha.coord.y - (cobrinha.coord.y - inty*20);
            cobrinha.tempo = 0;
        }
    }

    return cobrinha;

}

COBRINHA inicializa_cobrinha(COBRINHA cobrinha, int x, int y, int ed)
{

    cobrinha.coord.x = x;
    cobrinha.coord.y = y;
    cobrinha.coord.xm = x;
    cobrinha.coord.ym = y;
    cobrinha.tempo = 0;
    cobrinha.esq_dir = ed;
    cobrinha.vpulo = 100;
    
    cobrinha.bmp_mov = malloc(sizeof(BITMAP)*5);

    cobrinha.bmp_mov[0] = load_bitmap("imagens/cobrinha1_dir1.bmp", NULL);
    cobrinha.bmp_mov[1] = load_bitmap("imagens/cobrinha1_dir2.bmp", NULL);
    cobrinha.bmp_mov[2] = load_bitmap("imagens/cobrinha1_esq1.bmp", NULL);
    cobrinha.bmp_mov[3] = load_bitmap("imagens/cobrinha1_esq2.bmp", NULL);
    cobrinha.bmp_mov[4] = load_bitmap("imagens/cobrinha1_amassada.bmp", NULL);
   
    cobrinha.bmp_padrao = cobrinha.bmp_mov[0];
    
    cobrinha.bmp = cobrinha.bmp_padrao;
    cobrinha.buffer = create_bitmap(20, 20);
    
    return cobrinha;
}

JOGADOR inicializa_jogador(JOGADOR jogador, int x, int y, int ed, int novo_jogo)
{
    jogador.coord.x = x;
    jogador.coord.y = y;
    jogador.coord.xm = x;
    jogador.coord.ym = y;
    jogador.tempo = 0;
    jogador.esq_dir = ed;
    jogador.marretando = 0;
    jogador.vpulo = 150;
    jogador.comeca_cair = 0;
    jogador.comeca_pular = 1;
    jogador.para_pular = 0;
    if (novo_jogo)
    {
        jogador.vidas = 3;
        jogador.broas = 0;
    }
    
    jogador.bmp_mov = malloc(sizeof(BITMAP)*6);
    jogador.bmp_marreta = malloc(sizeof(BITMAP)*4);
    
    jogador.bmp_mov[0] = load_bitmap("imagens/jogador_dir1.bmp", NULL);
    jogador.bmp_mov[1] = load_bitmap("imagens/jogador_dir2.bmp", NULL);
    jogador.bmp_mov[2] = load_bitmap("imagens/jogador_dir3.bmp", NULL);
    jogador.bmp_mov[3] = load_bitmap("imagens/jogador_esq1.bmp", NULL);
    jogador.bmp_mov[4] = load_bitmap("imagens/jogador_esq2.bmp", NULL);
    jogador.bmp_mov[5] = load_bitmap("imagens/jogador_esq3.bmp", NULL);
    
    jogador.bmp_marreta[0] = load_bitmap("imagens/jogador_dir1_marreta1.bmp", NULL);
    jogador.bmp_marreta[1] = load_bitmap("imagens/jogador_dir1_marreta2.bmp", NULL);
    jogador.bmp_marreta[2] = load_bitmap("imagens/jogador_esq1_marreta1.bmp", NULL);
    jogador.bmp_marreta[3] = load_bitmap("imagens/jogador_esq1_marreta2.bmp", NULL);

    jogador.bmp_padrao = jogador.bmp_mov[0];
    
    jogador.bmp = jogador.bmp_padrao;
    jogador.buffer = create_bitmap(20, 20);
    
    return jogador;
}

void pegar_broas(JOGADOR *jogador, MAPA *mapa, BITMAP *bmp_ceu)
{
    if (mapa->matriz[jogador->omc.mim][jogador->omc.mmjm] == 1)
    {
        jogador->broas++;
        mapa->matriz[jogador->omc.mim][jogador->omc.mmjm] = 0;
        draw_sprite(screen, bmp_ceu, jogador->omc.mjm * 20, jogador->omc.mim * 20);

    }
}

void inicializar_jogo (JOGADOR *jogador, COBRINHA *cobrinhas, int novo_jogo)
{

    cobrinhas[0] = inicializa_cobrinha(cobrinhas[0], 200, 5, 0);
    cobrinhas[1] = inicializa_cobrinha(cobrinhas[1], 600, 5, 0);
    cobrinhas[2] = inicializa_cobrinha(cobrinhas[2], 900, 5, 1);
    cobrinhas[3] = inicializa_cobrinha(cobrinhas[3], 1200, 5, 0);
    cobrinhas[4] = inicializa_cobrinha(cobrinhas[4], 1600, 5, 0);
    cobrinhas[5] = inicializa_cobrinha(cobrinhas[5], 1900, 5, 1);
    cobrinhas[6] = inicializa_cobrinha(cobrinhas[6], 2200, 5, 0);
    cobrinhas[7] = inicializa_cobrinha(cobrinhas[7], 2300, 5, 1);
    
    *jogador = inicializa_jogador(*jogador, 20, 20, 1, novo_jogo);
}
