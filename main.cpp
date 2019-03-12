#include <utility>

#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include "ImportadorBmp.h"

using namespace std;

vector<GLdouble> coordenadas;
GLuint ID;
ImportadorBmp *importadorBmp;

void lerArquivo();

void carregarTextura(const char *nomeArquivo);

void keyboard(unsigned char key, int x, int y);

void init();

void display();

void lerArquivo() {
	/**
	 * Realiza a leitura do arquivo de coordenadas do qual sera
	 * desenhado o poligono que portara a figura
	 */
	try {
		ifstream arquivo;
		string linha;
		
		arquivo.open("arquivo.txt", ios_base::in);
		
		if (arquivo.is_open()) {
			while (!arquivo.eof()) {
				getline(arquivo, linha);
				istringstream iss(linha);
				string numero;
				while (getline(iss, numero, ',')) {
					coordenadas.push_back(stod(numero));
				}
			}
		} else {
			throw string("Arquivo não foi aberto devidamente.");
		}
	} catch (string &msg) {
		throw string(msg);
	}
}

void carregarTextura(const char *nomeArquivo) {
	/**
	 * Carrega as texturas da imagem a partir de uma classe criada para facilitar a importacao
	 * da imagem. A construcao das texturas eh feita atraves de um vetor de chars que armazena
	 * os bytes do bitmap da figura.
	 */
	try {
		importadorBmp = new ImportadorBmp(nomeArquivo);
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, importadorBmp->largura, importadorBmp->altura,
		                  GL_RGB, GL_UNSIGNED_BYTE, importadorBmp->textura);
	} catch (string &msg) {
		throw string(msg);
	}
}

int main(int argc, char **argv) {
	/**
	 * Funcao principal onde sao chamadas as funcoes de leitura do arquivo, carregamento de
	 * textura e funcoes padroes do OpenGL
	 */
	try {
		lerArquivo();
		
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowSize(300, 300);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Desenhando figuras");
		init();
		carregarTextura("dog.bmp");
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboard);
		glutMainLoop();
		
	} catch (string &msg) {
		cout << msg << endl;
	}
	return 0;
}

void init() {
	/**
	 * Funcao de inicializacao dos parametros do OpenGL, prepara a janela para a construcao
	 */
	glClearColor(1.0, 1.0, 1.0, 0);
	glOrtho(0, 300, 0, 300, -1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}


void display() {
	/**
	 * Funcao mais importante onde a textura eh renderizada dentro do poligono criado
	 * a partir dos pontos armazenados no arquivo. O primeiro poligono nao tem o preenchimento
	 * da figura, somente o segundo poligono eh preenchido
	 */
	GLdouble *pontos = coordenadas.data();
	glClear(GL_COLOR_BUFFER_BIT);
	
	// preparando para plotar a textura da imagem
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID);
	COLORREF cor = 0xFFFFFF;
	float cores[3] = {GetRValue(cor) / 255.0f,
	                  GetGValue(cor) / 255.0f,
	                  GetBValue(cor) / 255.0f};
	glColor3f(cores[0], cores[1], cores[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	// plotando a textura da imagem no poligono
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(pontos[0], pontos[1]);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(pontos[2], pontos[3]);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(pontos[4], pontos[5]);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(pontos[6], pontos[7]);
	glEnd();
	
	// preparando para desenhar o poligono sem preenchimento da imagem
	cor = 0x000000;
	cores[0] = GetRValue(cor) / 255.0f;
	cores[1] = GetGValue(cor) / 255.0f;
	cores[2] = GetBValue(cor) / 255.0f;
	glColor3f(cores[0], cores[1], cores[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3);
	
	// desenhando poligono sem preenchimento
	glBegin(GL_POLYGON);
	glVertex2d(pontos[0], pontos[1] + 160);
	glVertex2d(pontos[2], pontos[3] + 160);
	glVertex2d(pontos[4], pontos[5] + 160);
	glVertex2d(pontos[6], pontos[7] + 160);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
		default:
			break;
	}
}
