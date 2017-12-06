#include "jogo.h"

#include <GL/glut.h>
#include <iostream>
#include <fstream>

using namespace std;

/* Constantes */
#define LINHAS 40.0
#define COLUNAS 40.0

/* Variáveis globais */
int pontuacao = 0;

extern int direcaoCobrinha;

bool gameOver = false;

/* Protótipos */
void initialize(void);
void display(void);
void projection(void);
void reshape(int w, int h);
void keyboard(unsigned char tecla, int x, int y);
void special(int tecla, int x, int y);
void timer(int);

void initialize(void){
    /* Define a cor de fundo da janela */
    glClearColor(0.2, 0.8, 0.2, 0.0);
    
    grade(COLUNAS, LINHAS);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    desenhaGrade();
    desenhaComida();
    desenhaCobrinha();

    /* Classes do fstream */
    ofstream arquivoEscrita;
    ifstream arquivoLeitura;

    if(gameOver){
        /* Abre o arquivo em modo escrita */
        arquivoEscrita.open("pontuacao.dat");
        
        /* Escreve no arquivo */
        arquivoEscrita << pontuacao << endl;
        
        /* Fecha o arquivo em modo escrita */
        arquivoEscrita.close();
        
        /* Abre o arquivo em modo leitura */
        arquivoLeitura.open("pontuacao.dat");
        
        /* Imprime a pontuação */
        char info[4];
        arquivoLeitura >> info;
        cout << info;
        char texto[50] = "Seus Pontos: ";
        strcat(texto, info);
        MessageBox(NULL, texto, "Game Over", 0);
        exit(0);
    }
    
    glutSwapBuffers();
}

void projection(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0.0, COLUNAS, 0.0, LINHAS, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(int w, int h){
    glViewport(0, 0, (GLfloat)w, GLfloat(h));
    
    projection();
}

void keyboard(unsigned char tecla, int x, int y){
    switch(tecla){
        case 'w':
        case 'W':
            if(direcaoCobrinha != BAIXO){
                direcaoCobrinha = CIMA;
            }
            break;
        case 's':
        case 'S':
            if(direcaoCobrinha != CIMA){
                direcaoCobrinha = BAIXO;
            }
            break;
        case 'd':
        case 'D':
            if(direcaoCobrinha != ESQUERDA){
                direcaoCobrinha = DIREITA;
            }
            break;
        case 'a':
        case 'A':
            if(direcaoCobrinha != DIREITA){
                direcaoCobrinha = ESQUERDA;
            }
            break;
    }
    glutPostRedisplay();
}

void special(int tecla,int x,int y){
    switch(tecla){
        case GLUT_KEY_UP:
            if(direcaoCobrinha != BAIXO){
                direcaoCobrinha = CIMA;
            }
            break;
        case GLUT_KEY_DOWN:
            if(direcaoCobrinha != CIMA){
                direcaoCobrinha = BAIXO;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(direcaoCobrinha != ESQUERDA){
                direcaoCobrinha = DIREITA;
            }
            break;
        case GLUT_KEY_LEFT:
            if(direcaoCobrinha != DIREITA){
                direcaoCobrinha = ESQUERDA;
            }
            break;
    }
    glutPostRedisplay();
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

int main(int argc, char **argv){
    /* Escopo de criação de janela*/
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Jogo da Cobrinha");
    
    /* Background */
    initialize();
    
    /* Escopo de registro de callbacks */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);        /* Só para teclas da tabela ASCII */
    glutSpecialFunc(special);          /* Teclas especiais */
    glutTimerFunc(100, timer, 0);
    
    glutMainLoop();
    
    return 0;
}
