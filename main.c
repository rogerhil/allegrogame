#include "main.h"
#include "estruturas.h"
#include "arquivo.h"
#include "funcoes.h"



volatile long int fps = 0;

void inicializar_allegro(int criar_cen)
{
    allegro_init();
    install_keyboard();	
    install_timer();	
    install_mouse();	
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, res_larg, res_alt, 0, 0);	
    
    LOCK_VARIABLE(fps);	LOCK_FUNCTION(cont_fps);	
     
    install_int_ex(cont_fps, BPS_TO_TIMER(60));	
}

void cont_fps(){
    fps++;
    
}END_OF_FUNCTION(cont_fps);

int main(void){	

    inicializar_allegro(0);
    
    MAPA mapa;
    BITMAP *jogador_ant;
    BITMAP *bmp_ceu;
    BITMAP *bmp_broa;
    BITMAP *bmp_muro_quebrado;
    JOGADOR jogador;
    COBRINHA *cobrinhas;
    
    int k, w, cont_mb = 0;
    int matou_bicho = 0;
    int passo = 0, p = 0;
    int n_cobrinhas = 8;

    cobrinhas = malloc(sizeof(COBRINHA)*n_cobrinhas);

    inicializar_jogo (&jogador, cobrinhas, 1);
    
    BITMAP *main_buffer = create_bitmap(res_larg, res_alt);
    BITMAP *prox_buffer = create_bitmap(20, res_alt);    

    mapa = define_mapa_padrao();     
   
    
    
    bmp_ceu = load_bitmap("imagens/ceu1.bmp", NULL);
    bmp_muro_quebrado = load_bitmap("imagens/muro1_quebrado.bmp", NULL);
    bmp_broa = load_bitmap("imagens/broa1.bmp", NULL);
    
       

    
    main_buffer = desenha_mapa(mapa, main_buffer, 0, res_larg / 20);
    prox_buffer = desenha_mapa(mapa, prox_buffer, (res_larg / 20) -1 + passo, (res_larg / 20) + passo);

    draw_sprite(screen, main_buffer, 0, 0);
    
    desenha_buffer(jogador.buffer, jogador.bmp, jogador.coord.x, jogador.coord.y);
    
    for (k = 0; k < n_cobrinhas; k++)
    {
        desenha_buffer(cobrinhas[k].buffer, cobrinhas[k].bmp, cobrinhas[k].coord.x, cobrinhas[k].coord.y);
    }    
    
    int ttt = 0;
    int tmarreta = 10;
    int tm, time_jogo;

    int mjff;
    int cen_and = 0;
    
    int local, local2;

    int v_min = 1;
    int v_max = 2;
    int velocidade = v_min;
    
    //int broas = 0;
    int morreu = 0;

    char bstr[20];
    char str_broas[30] = "Broas: ";    
    char vstr[20];
    char str_vidas[30] = "Vidas: ";


    int px, py;
    
    sprintf(vstr, "%d", jogador.vidas);
    strcat(str_vidas, vstr);
    textprintf(screen, font, 10, 10, makecol(255,255,255), str_vidas);
        
    while(!key[KEY_ESC] & !morreu)
    {
       
        ttt++;
        
        if (ttt > 2000000)
        {
            ttt = 0;
            time_jogo++;

            jogador.omc.mi0 = (jogador.coord.y) / 20;
            jogador.omc.mi1 = (jogador.coord.y + 20) / 20;
            jogador.omc.mim = (jogador.coord.y + 10) / 20;
            jogador.omc.mj0 = (jogador.coord.x) / 20;
            jogador.omc.mj1 = (jogador.coord.x + 20) / 20;
            jogador.omc.mjm = (jogador.coord.x + 10) / 20;
            jogador.omc.mmj0 = (jogador.coord.xm) / 20;
            jogador.omc.mmj1 = (jogador.coord.xm + 20) / 20;
            jogador.omc.mmjm = (jogador.coord.xm + 10) / 20;
            
            local = mapa.matriz[jogador.omc.mi1][jogador.omc.mmjm];
            local2 = mapa.matriz[jogador.omc.mi1 - 1][jogador.omc.mmjm];
            
            px = jogador.coord.x;
            py = jogador.coord.y;

            for (k = 0; k < n_cobrinhas; k++)
            {
                cobrinhas[k].coord.px = cobrinhas[k].coord.x;
                cobrinhas[k].coord.py = cobrinhas[k].coord.y;
            }
            
            
            for (k = 0; k < n_cobrinhas; k++)
            {
                if (jogador.omc.mim == ((cobrinhas[k].coord.y + 10) /20) &
                    jogador.omc.mjm == ((cobrinhas[k].coord.x + 10) /20))
                {
                    printf("pegou");
                    textprintf(screen, font, 120, 220, makecol(255,255,255), "  PERDEU ! ! !  ");
                    inicializar_jogo (&jogador, cobrinhas, 0);
                    if (jogador.vidas == 0)
                        morreu = 1;
                    jogador.vidas -= 1;
                    
                    printf("%d", jogador.vidas);
                    strcpy(str_vidas, "Vidas: ");
                    sprintf(vstr, "%d", jogador.vidas);
                    strcat(str_vidas, vstr);
                    
                    passo = 0;
                    p = 0;
                    main_buffer = desenha_mapa(mapa, main_buffer, 0, res_larg / 20);
                    prox_buffer = desenha_mapa(mapa, prox_buffer, (res_larg / 20) -1 + passo, (res_larg / 20) + passo);
                    while(!key[KEY_ENTER])
                    {
                    }
                    draw_sprite(screen, main_buffer, 0, 0);
                    desenha_buffer(jogador.buffer, jogador.bmp, jogador.coord.x, jogador.coord.y);
                    for (k = 0; k < n_cobrinhas; k++)
                    {
                        desenha_buffer(cobrinhas[k].buffer, cobrinhas[k].bmp, cobrinhas[k].coord.x, cobrinhas[k].coord.y);
                    }
                }
                
                if (jogador.omc.mi1 == ((cobrinhas[k].coord.y + 10) /20) &
                    jogador.omc.mjm == ((cobrinhas[k].coord.x + 10) /20))
                {
                    draw_sprite(screen, cobrinhas[k].bmp_mov[4], cobrinhas[k].coord.x, cobrinhas[k].coord.y);
                    n_cobrinhas--;
                    matou_bicho = 1;
                    for (w = k; w < n_cobrinhas; w++)
                    {
                        cobrinhas[w] = cobrinhas[w + 1];
                    }
                }
            }
            if (matou_bicho)
            {
                cont_mb++;
                jogador.vpulo = 400;
                jogador.para_pular = 0;
            }
            
            if (cont_mb > 7)
            {
                cont_mb = 0;
                matou_bicho = 0;
                jogador.para_pular = 1;
                jogador.vpulo = 150;
                jogador.tempo = 0;
            }
            
            

            
            for (k = 0; k < n_cobrinhas; k++)
            {            
                cobrinhas[k] = movimenta_cobrinha(cobrinhas[k], mapa, jogador);
            }
            
	    pegar_broas(&jogador, &mapa, bmp_ceu);
	    
            if ((!key[KEY_S] | jogador.para_pular) & !matou_bicho)
            {
                jogador = fcair(jogador, local);
            }
            if (key[KEY_S] & !jogador.para_pular & !jogador.para_pular | matou_bicho)
            {
                jogador = fpular(jogador, local2);
            }

            if (key[KEY_Q])
            {
                velocidade = v_max;
            }
            else
            {
                velocidade = v_min;
            }
            
            if (key[KEY_A] & (!jogador.marretando))
            {
                jogador = marretar(jogador, mapa, bmp_muro_quebrado, bmp_ceu, bmp_broa, p);
                tm = time_jogo;
            }

            if ((jogador.marretando) & (time_jogo > tm + tmarreta))
            {
                jogador = marretando(jogador, &mapa, bmp_muro_quebrado, bmp_ceu, bmp_broa, p);
                tm = time_jogo;
            }      

            limpa_buffer(jogador.buffer, px, py);


            for (k = 0; k < n_cobrinhas; k++)
            {
                limpa_buffer(cobrinhas[k].buffer, cobrinhas[k].coord.px, cobrinhas[k].coord.py);
            }

            if (key[KEY_RIGHT])
            {
                jogador = anda_direita(jogador, &main_buffer, &prox_buffer, mapa, &p, &passo, velocidade);
                if (((jogador.coord.x + 2) >= res_larg / 2) &
                      ((jogador.coord.x + 2) <= res_larg / 2 + 20) &
                      (mapa.matriz[jogador.omc.mi1-1][jogador.omc.mmj1] < 10))
                {
                    for (k = 0; k < n_cobrinhas; k++)
                    {
                        cobrinhas[k].coord.x -= 1;
                    }
                }
            }

            if (key[KEY_LEFT] & jogador.coord.x > -1)
            {
                jogador = anda_esquerda(jogador, mapa, velocidade);
            }


            desenha_buffer(jogador.buffer, jogador.bmp, jogador.coord.x, jogador.coord.y);
            
            for (k = 0; k < n_cobrinhas; k++)
            {
                desenha_buffer(cobrinhas[k].buffer, cobrinhas[k].bmp, cobrinhas[k].coord.x, cobrinhas[k].coord.y);
            }

            sprintf(bstr, "%d", jogador.broas);
            strcpy(str_broas, "Broas: ");
            strcat(str_broas, bstr);    
            
            textprintf(screen, font, 20, 10, makecol(255,255,255), str_vidas);
            textprintf(screen, font, 20, 18, makecol(255,255,255), str_broas);
            draw_sprite(screen, bmp_ceu, 0, 0);
            draw_sprite(screen, bmp_ceu, 0, 20);
        }
    }
   
    while(!key[KEY_ESC])
    {
        textprintf(screen, font, 25, 102, makecol(255,255,255), "                                 ");
        textprintf(screen, font, 25, 110, makecol(255,255,255), "       G A M E     O V E R       ");
        textprintf(screen, font, 25, 118, makecol(255,255,255), "                                 ");
    }
            
    return(0);
    
}END_OF_MAIN();

