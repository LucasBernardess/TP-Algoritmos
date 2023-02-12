#include <jogo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobra.h"


int main(){
    // Nick
    char nick[15];
    printf("Digite o seu nick: ");
    scanf("%s", nick);

    //variavel referente as telas, pontuacao, coordenadas e funcoes

    int tela = 0; //variavel que identifica a tela que esta sendo mostrada dependendo da dificuldade
    int score = 0; //variavel que indica a pontuação do jogador
    int LadoX = 320; //variavel que identifica as coordenadas de movimentação da cobra em X
    int LadoY = 240;//variavel que identifica as coordenadas de movimentação da cobra em Y
    int FrutaX;//variavel que identifica as coordendas da Fruta em X
    int FrutaY;//variavel que identifica as coordenadas da Fruta em Y
    int desenhaFruta = 0;//contador para desenhar Fruta, se for igual a 1 a fruta é desenhada em uma posição aleatória
    int x = 640;//tamanho de matriz em x
    int y = 480;//tamanho de matriz em y
    int direcao = 3;//variavel de identificação do lado que a cobra está andando
    int corpoX[30000];//vetor que armazena as coordenadas do corpo da cobra em x
    int corpoY[30000];//vetor que armazena as coordenadas da cobra em Y
    int contador = 0;//contador que armazena o tamanho da cobra de acordo com quantas frutas foram pegas
    int colisaoCobra = 0; // quando for igual a 1 significa que a cobra banteu nela msm
    static int indice = 0; //impede o loop na hora do ranking
    int matriz[x][y];//matriz do plano cartesiano
    
    //funcoes

    void geradorDeFrutas(){// função utilizada para gerar a fruta em um lugar aleatório da tela, primeiramente ela verifica se já tem algo na posição, se tiver ela gera outro número,
             if(desenhaFruta == 0){                                                                 //se não tiver nada ela gera a fruta na posição 
                FrutaX = 10 + rand() % 610;
                FrutaY = 30 + rand() % 430;
                for(int i = 1; i<10; i++){
                    if(FrutaX % 10 == i){
                        if(i>=6){
                            FrutaX += 10 - i;
                        }else{
                            FrutaX -= i;
                        }
                    }
                }
                for(int i = 1; i<10; i++){
                    if(FrutaY % 10 == i){
                        if(i>=6){
                            FrutaY += 10 - i;
                        }else{
                            FrutaY-= i;
                        }
                    }
                }
    
                if(matriz[LadoX][LadoY] == 0){
                    desenhaFruta = 1;
                }
            }

            if(desenhaFruta == 1){
                cor(VERMELHO);
                desenha_circulo(FrutaX, FrutaY, 5);
            }
        }   

    void pegaFruta(){   //função para identificar se a cobra pegou a Fruta
            if(((FrutaX/10)-1) == (LadoX/10) && ((FrutaY/10)-1) == (LadoY/10)){
                if(tela==1){
                    score++;
                     if(!som_esta_tocando("assets/conquista.wav")){
                        toca_som("assets/conquista.wav");
                    }
                    contador+=50;
                    desenhaFruta=0;
                }else if(tela==2){
                    score+=2;
                    if(!som_esta_tocando("assets/conquista.wav")){
                        toca_som("assets/conquista.wav");
                    }
                    contador+=50;
                    desenhaFruta=0;
                }else if(tela==3){
                    score+=3;
                    if(!som_esta_tocando("assets/conquista.wav")){
                        toca_som("assets/conquista.wav");
                    }
                    contador+=50;
                    desenhaFruta=0;
                }

            }
         
    }  

    // abrir e fechar tela
    abre_janela(640, 480);
        while(janela_esta_aberta()) {
            if(tecla_pressionada(ESC)){
                janela_deve_fechar();
            }

        //tela de login

        if(tela == 0){
           //valores das variaveis de inicio de cada partida
            LadoX = 320;
            LadoY = 240;
            contador = 0;
            score = 0;
            colisaoCobra = 0;
            indice = 0;
           
            desenha_imagem(320, 240, "assets/login.png");

            if(!som_esta_tocando("assets/temaBase.wav")){
                toca_som_em_loop("assets/temaBase.wav");
            }    

            //selecionar dificuldade, uma variavel é atribuida a cada dificuldade para abrir a tela 

            if(tecla_acabou_de_ser_apertada(F1)){
                tela = 1; //dificuldade facil
            }
            else if(tecla_acabou_de_ser_apertada(F2)){
                tela = 2; //dificuldade media 
            }
            else if(tecla_acabou_de_ser_apertada(F3)){
                tela = 3; //dificuldade rapido
            }
            else if(tecla_acabou_de_ser_apertada(F4)){
                tela = 5; //tela de ranking
            }
        }    

        //abrir a tela selecionada dependendo da dificuldade

        if(tela == 1){
            //imagem e cabecario da tela com score
    
            cabecario(score,nick);
            
            if(!som_esta_tocando("assets/temaBase.wav")){
                toca_som_em_loop("assets/temaBase.wav");
            } 

            //cria a cabeça da cobra

            geraCobra(LadoX, LadoY);

            //movimentos da cobra
            
            direcao = movimentacao(direcao);


            if(direcao == 1){ //movimenta a cabeça da cobra
                LadoX += 2;
            }else if(direcao == 2){
                LadoX -= 2;
            }else if(direcao == 3){
                LadoY -= 2;
            }else if(direcao == 4){
                LadoY += 2;
            }   

            //verifica colisao

            if(colisaoCobra == 0){
            for(int i = 0; i<contador; i+=10){
                if(LadoX == corpoX[i/10] && LadoY == corpoY[i/10]){
                    colisaoCobra++;
                    }
                }
            }else if(colisaoCobra == 1){
                tela = 5;
                
            }


            //Fruta
            
            geradorDeFrutas(desenhaFruta, FrutaX, FrutaY, x, y, matriz, LadoX, LadoY);
            pegaFruta();

            //cobra aumenta a cada fruta comida

            corpoCobra(contador, corpoX, corpoY);

            novaCabeca(direcao, contador, corpoX, corpoY, LadoX, LadoY);


            //limitantes dos lados

            if(LadoX>639 || LadoX<0 || LadoY<0 || LadoY>479){
                 tela = 5;
                 
            }
        }

        if(tela == 2){
            //imagem e cabecario da tela com score

            cabecario(score,nick);
            
            if(!som_esta_tocando("assets/temaBase.wav")){
                toca_som_em_loop("assets/temaBase.wav");
            }             

            //cria a cabeça da cobra

            geraCobra(LadoX, LadoY);

            //movimentos da cobra
            
            direcao = movimentacao(direcao);
           
            if(direcao == 1){ //movimenta a cabeça da cobra
                LadoX += 4;
            }else if(direcao == 2){
                LadoX -= 4;
            }else if(direcao == 3){
                LadoY -= 4;
            }else if(direcao == 4){
                LadoY += 4;
            }   

            //verifica colisao

            if(colisaoCobra == 0){
                for(int i = 0; i<contador; i+=10){
                    if(LadoX == corpoX[i/10] && LadoY == corpoY[i/10]){
                        colisaoCobra++;
                    }
                }
            }else if(colisaoCobra == 1){
                tela = 5;
               
            }

            //Fruta
            
            geradorDeFrutas(desenhaFruta, FrutaX, FrutaY, x, y, matriz, LadoX, LadoY);
            pegaFruta();

            //cobra aumenta a cada fruta comida

            corpoCobra(contador, corpoX, corpoY);

            novaCabeca(direcao, contador, corpoX, corpoY, LadoX, LadoY);

            //limitantes dos lados

            if(LadoX>639 || LadoX<0 || LadoY<0 || LadoY>479){
                 tela = 5;
                 
            } 
        }
        
        if(tela == 3){
            //imagem e cabecario da tela com score

            cabecario(score,nick);
            
            if(!som_esta_tocando("assets/temaBase.wav")){
                toca_som_em_loop("assets/temaBase.wav");
            } 
            
            //cria a cabeça da cobra

            geraCobra(LadoX, LadoY);

            //movimentos da cobra
            
            direcao = movimentacao(direcao);
           
            if(direcao == 1){ //movimenta a cabeça da cobra
                LadoX += 5;
            }else if(direcao == 2){
                LadoX -= 5;
            }else if(direcao == 3){
                LadoY -= 5;
            }else if(direcao == 4){
                LadoY += 5;
            }   

            //verifica colisao

            if(colisaoCobra == 0){
                for(int i = 0; i<contador; i+=10){
                    if(LadoX == corpoX[i/10] && LadoY == corpoY[i/10]){
                        colisaoCobra++;
                    }
                }
            }else if(colisaoCobra == 1){
                tela = 5;
               
            }

            //Fruta
            
            geradorDeFrutas(desenhaFruta, FrutaX, FrutaY, x, y, matriz, LadoX, LadoY);
            pegaFruta();

            //cobra aumenta a cada fruta comida

            corpoCobra(contador, corpoX, corpoY);

            novaCabeca(direcao, contador, corpoX, corpoY, LadoX, LadoY);


            //limitantes dos lados

            if(LadoX>639 || LadoX<0 || LadoY<0 || LadoY>479){
                 tela = 5;
                
            } 
        }

        //tela de ranking

        if(tela == 4){
            if(som_esta_tocando("assets/derrota.wav")){
                para_som("assets/derrota.wav");
            } 
            if(!som_esta_tocando("assets/temaBase.wav")){
                recomeca_som("assets/temaBase.wav");
            } 
            desenha_imagem(320, 240, "assets/ranking.jpg");
            
            if(indice < 1){

                int *VetorScore = malloc(sizeof(int* )* 5);
                char **MatrizN = malloc(sizeof(char* ) *5);
                for (int i=0; i<5; i++){ MatrizN[i] = (char*) malloc (15 *sizeof(char)); }
                FILE *rankingL = fopen("assets/ranking2.txt", "r");

                char buf[125];
                int cont = 0;
                int scoreL;
                char nomeL[15];

                if(rankingL != NULL){
                    fgets(buf, 125,rankingL);
                    while(!feof(rankingL) && cont<5){
                        strcpy(nomeL, strtok(buf, ","));
                        scoreL = atoi(strtok(NULL,","));
                        VetorScore[cont] = scoreL;
                        for(int i = 0; i<15; i++){
                            MatrizN[cont][i] = nomeL[i];
                        }
                        fgets(buf, 125, rankingL);
                        cont++;
                    }
                }
                fclose(rankingL);


                FILE *ranking = fopen("assets/ranking2.txt", "w");
                
                if(score>VetorScore[4]){
                    VetorScore[4] = score;
                    MatrizN[4] = nick;
                }
                for(int i = 0; i<5; i++){
                    for(int j = 0; j<5; j++){
                        if(i != j){
                            if(VetorScore[j]< VetorScore[i]){
                                int CopiaS = VetorScore[i];
                                VetorScore[i] = VetorScore[j];
                                VetorScore[j] = CopiaS;
                                char *copiaN = MatrizN[i];
                                MatrizN[i] = MatrizN[j];
                                MatrizN[j] = copiaN;
                            }
                        }
                    }
                }
                
                char vetorScore2[10];
                for(int i = 0; i<5; i++){
                    itoa(VetorScore[i], vetorScore2, 10);
                    fputs(MatrizN[i], ranking);
                    fputc(',',ranking);
                    fputs(vetorScore2, ranking);
                    fputc(',',ranking);
                    fputc('\n', ranking);
                }
                fclose(ranking);
                
                printf("---------RANKING---------\n");

                for(int i = 0; i<5; i++){
                    printf("PLAYER ---> %s\n", MatrizN[i]);
                    printf("SCORE ----> %d\n", VetorScore[i]);
                    printf("\n");
                }
            } 
            indice ++;

            if(tecla_acabou_de_ser_apertada(ENTER)){
                    tela = 0;
            }
        }    
        
        //tela de game over
        
        if(tela == 5){
            desenha_imagem(320, 240, "assets/game over.jpg");
            if(som_esta_tocando("assets/temaBase.wav")){
                para_som("assets/temaBase.wav");
            } 
            if(!som_esta_tocando("assets/derrota.wav")){
                toca_som("assets/derrota.wav");
            } 
            cor(BRANCO);
            desenha_texto(160, 389, "Pressione F4 para ver o ranking");
            fonte("assets/ubuntu.ttf", 20); 
            desenha_texto(257, 409, "Score: %d", score);
            
            if(tecla_acabou_de_ser_apertada(F4)){
                tela = 4;
            }
        }
    }
}

