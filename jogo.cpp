#include "jogo.h"

#include <GL/glut.h>
#include <iostream>
#include <ctime>

using namespace std;

/* Protótipos */
void grade(int x, int y);
void desenhaGrade(void);
void desenhaComida(void);
void desenhaCobrinha(void);
void unidade(int x, int y);
int aleatorio(int _min, int _max);

int linhas = 0,
    colunas = 0,
    
    comidaX,
    comidaY,
    
    direcaoCobrinha = DIREITA,
    comprimentoCobrinha = 1,
    posicaoCobrinhaX[MAXIMO + 1] = {4, 3, 2, 1, 0, -1, -1},
    posicaoCobrinhaY[MAXIMO + 1] = {10, 10, 10, 10, 10, 10, 10};

extern int pontuacao;

bool comida = false,
     aumentaComprimento = false,
     sinalizacao = false;

extern bool gameOver;

void grade(int x, int y){
    colunas = x;
    linhas = y;
}

void desenhaGrade(void){
    for(int i = 0; i < colunas; i++){
        for(int j = 0; j < linhas; j++){
            unidade(i, j);
        }
    }
}

void desenhaComida(void){
    /* Seta a posição da comida aleatóriamente */
    if(!comida){
        comidaX = aleatorio(2, colunas - 2);
        comidaY = aleatorio(2, linhas - 2);
        
        cout << comidaX << comidaY << endl;
        comida = true;
    }
    
    /* Se comida = true, desenha a comida na posição gerada */
    glBegin(GL_QUADS);
        glVertex2d(comidaX, comidaY);
        glVertex2d(comidaX + 1, comidaY);
        glVertex2d(comidaX + 1, comidaY + 1);
        glVertex2d(comidaX, comidaY + 1);
    glEnd();
}

void desenhaCobrinha(void){
    for(int i = comprimentoCobrinha - 1; i > 0; i--){
        posicaoCobrinhaX[i] = posicaoCobrinhaX[i - 1];
        posicaoCobrinhaY[i] = posicaoCobrinhaY[i - 1];
    }
    
    for(int i = 0; i < comprimentoCobrinha; i++){
        glColor3f(0.11, 0.11, 0.11);
    
        if(i == 0){
            glColor3f(0.0, 0.0, 0.0);
            
            switch(direcaoCobrinha){
                case CIMA:
                    posicaoCobrinhaY[i]++;
                    break;
                case BAIXO:
                    posicaoCobrinhaY[i]--;
                    break;
                case DIREITA:
                    posicaoCobrinhaX[i]++;
                    break;
                case ESQUERDA:
                    posicaoCobrinhaX[i]--;
                    break;
            }
            
            /*
            / Se a posição da cobrinha for igual as unidades da grade - colisão
            / O jogo dá Game Over
            */
            if(posicaoCobrinhaX[i] == 0 || posicaoCobrinhaX[i] == colunas - 1 ||
               posicaoCobrinhaY[i] == 0 || posicaoCobrinhaY[i] == linhas - 1){
               gameOver = true;
               
            /*
            / Se a posição da cobrinha for igual a posição da comida
            / A comida "some", a pontuação incrementa...
            */
            } else if(posicaoCobrinhaX[i] == comidaX && posicaoCobrinhaY[i] == comidaY){
                comida = false;
                pontuacao++;
                
                /*
                / E se comprimentoCobrinha for menor ou igual a constante MAXIMO
                / Seta aumentaComprimento como verdadeiro
                */
                if(comprimentoCobrinha <= MAXIMO){
                    aumentaComprimento = true;
                }
                
                /* Mensagem de vitória */
                if(comprimentoCobrinha == MAXIMO){
                    MessageBox(NULL, "Você ganhou!\nVocê pode continuar jogando, porém a cobrinha não crescerá mais!", "Parabéns!", 0);
                }
            }
            
            for(int j = 1; j < comprimentoCobrinha; j++){
                /*
                / Colisao da cobrinha nela mesma 
                / O jogo dá Game Over
                */
                if(posicaoCobrinhaX[j] == posicaoCobrinhaX[0] &&
                   posicaoCobrinhaY[j] == posicaoCobrinhaY[0]){
                    gameOver = true;  
                }
            }
        }
        
        glBegin(GL_QUADS);
            glVertex2d(posicaoCobrinhaX[i], posicaoCobrinhaY[i]);
            glVertex2d(posicaoCobrinhaX[i] + 1, posicaoCobrinhaY[i]);
            glVertex2d(posicaoCobrinhaX[i] + 1, posicaoCobrinhaY[i] + 1);
            glVertex2d(posicaoCobrinhaX[i], posicaoCobrinhaY[i] + 1);
        glEnd();
    }
    
    /*
    / Se aumentaComprimento for verdadeiro, incrementa o comprimento da cobrinha 
    / E seta aumentaComprimento como falso
    */
    if(aumentaComprimento){
        comprimentoCobrinha++;
        aumentaComprimento = false;
    }
}

void unidade(int x, int y){
    glLoadIdentity();
    
    /* Unidades da grade - colisão */
    if(x == 0 || x == colunas - 1 || y == 0 || y == linhas - 1){
        glLineWidth(3.0);
        glColor3f(0.13, 0.55, 0.13);
    /* Demais unidades da grade */
    } else {
        glLineWidth(1.0);
        glColor3f(0.13, 0.55, 0.13);
    }
    
    glBegin(GL_LINES);
        glVertex2d(x, y);
        glVertex2d(x + 1, y);
        glVertex2d(x + 1, y);
        glVertex2d(x + 1, y + 1);
        
        glVertex2d(x + 1, y + 1);
        glVertex2d(x, y + 1);
        glVertex2d(x, y + 1);
        glVertex2d(x, y);
    glEnd();
}

int aleatorio(int _min, int _max){
    if(!sinalizacao){
        srand(time(NULL));
        sinalizacao = true;
    } else{
        sinalizacao = false;
    }
    
    return _min + rand()%(_max - _min);
}
