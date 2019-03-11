#include <utility>

#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include "ImportadorBmp.h"

using namespace std;

vector<GLdouble> coordenadas;
bool preenchimento;
GLuint ID;
ImportadorBmp *importadorBmp;

const GLubyte dog_map[] = {};

void lerArquivo();

void carregarTextura(string nomeArquivo);

void keyboard(unsigned char key, int x, int y);

void init();

void display();

void reshape(int w, int h);

void lerArquivo() {
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
	importadorBmp = new ImportadorBmp(nomeArquivo);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, importadorBmp->largura, importadorBmp->altura,
	                  GL_RGB, GL_UNSIGNED_BYTE, importadorBmp->textura);
}

int main(int argc, char **argv) {
	try {
		lerArquivo();
		char aux;
		cout << "Deseja preenchimento da figura? (s/n)" << endl;
		cin >> aux;
		preenchimento = aux == 's';
		
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowSize(300, 300);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Desenhando figuras");
		carregarTextura("dog.bmp");
		init();
		glutDisplayFunc(display);
//		glutReshapeFunc(reshape);
		glutKeyboardFunc(keyboard);
		glutMainLoop();
		
	} catch (string &msg) {
		cout << msg << endl;
	}
	return 0;
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0);
	glOrtho(0, 300, 0, 300, -1, 1);
}


void display() {
	GLdouble *pontos = coordenadas.data();
	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(1.0, 1.0, 1.0);
//	COLORREF cor = 0xFFFFFF;
//	float m_ColorR = GetRValue(cor) / 255.0f;
//	float m_ColorG = GetGValue(cor) / 255.0f;
//	float m_ColorB = GetBValue(cor) / 255.0f;
//	glColor3f(m_ColorR, m_ColorG, m_ColorB);
//
//	glEnable(GL_POLYGON_SMOOTH);
//	glEnable(GL_POLYGON_STIPPLE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

//	if (!preenchimento) {
//		glLineWidth(3);
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	}
	
	// texture coord 0
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_DOUBLE, 0, pontos);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_DOUBLE, 0, importadorBmp->textura);
	
	glDrawArrays(GL_POLYGON, 0, coordenadas.size() / 2);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, -10, -10, -10);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
		default:
			break;
	}
}
