#include <jogo.h>
#include "cobra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void cabecario(int score, char *nick){
            desenha_imagem(320, 240, "assets/template.jpg");
            cor(AMARELO);
            fonte("assets/ubuntu.ttf", 25); 
            desenha_texto(68, 20, "Score: %d", score);
            fonte("assets/ubuntu.ttf", 25); 
            desenha_texto(440, 20, "Jogador: %s", nick);
   }

int movimentacao(int direcao){
        if(tecla_acabou_de_ser_apertada(DIREITA) && direcao != 2){
                    direcao = 1;
        }else if(tecla_acabou_de_ser_apertada(ESQUERDA) && direcao != 1){
                    direcao = 2;
        }else if(tecla_acabou_de_ser_apertada(CIMA) && direcao != 4){
                    direcao = 3;
        }else if(tecla_acabou_de_ser_apertada(BAIXO) && direcao != 3){
                    direcao = 4;
        }

        return direcao;
    }

void geraCobra(int LadoX, int LadoY){
        cor(BRANCO);
        desenha_retangulo(LadoX,LadoY,10,10);//função que gera a cabeça da cobra, sempre no meio da tela e com o tamanho 10x10 
}

void corpoCobra(int contador, int *corpoX, int *corpoY){
            for(int i=0; i<contador; i+=10){ 
                if(i!=0){
                        cor(BRANCO);
                        desenha_retangulo(corpoX[i/10],corpoY[i/10],10,10);
                    
                }
            }
        } 

 

void novaCabeca(int direcao, int contador, int *corpoX, int *corpoY, int LadoX, int LadoY){
    if(direcao == 1){
                if(contador>20){
                    for(int i=(contador-10)/10; i>1; i--){//Armazena a coordenada do corpo anterior no seguinte
                        corpoX[i]=corpoX[(i-1)];
                        corpoY[i]=corpoY[(i-1)];
                    }//Faz o corpo seguir a cabeça
                }
                corpoX[1]=LadoX;
                corpoY[1]=LadoY;//Armazena a coordenada do primeiro segmento do corpo
        
             }else if(direcao == 2){
                if(contador>20){
                    for(int i=(contador-10)/10; i>1; i--){//Armazena a coordenada do corpo anterior no seguinte
                        corpoX[i]=corpoX[(i-1)];
                        corpoY[i]=corpoY[(i-1)];
                    }//Faz o corpo seguir a cabeça
                }
                corpoX[1]=LadoX;
                corpoY[1]=LadoY;//Armazena a coordenada do primeiro segmento do corpo

            }else if(direcao == 3){
                if(contador>20){
                    for(int i=(contador-10)/10; i>1; i--){//Armazena a coordenada do corpo anterior no seguinte
                        corpoX[i]=corpoX[(i-1)];
                        corpoY[i]=corpoY[(i-1)];
                    }//Faz o corpo seguir a cabeça
                }
                corpoX[1]=LadoX;
                corpoY[1]=LadoY;//Armazena a coordenada do primeiro segmento do corpoa
            
            }else if(direcao == 4){
                if(contador>20){
                    for(int i=(contador-10)/10; i>1; i--){//Armazena a coordenada do corpo anterior no seguinte
                        corpoX[i]=corpoX[(i-1)];
                        corpoY[i]=corpoY[(i-1)];
                    }//Faz o corpo seguir a cabeça
                }
                corpoX[1]=LadoX;
                corpoY[1]=LadoY;//Armazena a coordenada do primeiro segmento do corpo
            }

}
