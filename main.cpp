#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

vector<GLdouble> coordenadas;
bool preenchimento;

const GLubyte dog_map[] = {};

void lerArquivo();

void keyboard(unsigned char key, int x, int y);

void init();

void display();

void lerArquivo() {
	try {
		ifstream arquivo;
		string linha;

		arquivo.open("arquivo.txt", ios_base::in);

		if(arquivo.is_open()) {
			while(!arquivo.eof()) {
				getline(arquivo, linha);
				istringstream iss(linha);
				string numero;
				while(getline(iss, numero, ',')) {
					coordenadas.push_back(stod(numero));
				}
			}
		} else {
			throw string("Arquivo não foi aberto devidamente.");
		}
	} catch(string &msg) {
		throw string(msg);
	}
}

int main(int argc, char **argv) {
	try {
		lerArquivo();
		char aux;
		cout << "Deseja preenchimento da figura? (s/n)" << endl;
		cin >> aux;
		preenchimento = aux == 's';

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(300, 300);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Desenhando figuras");
		init();
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboard);
		glutMainLoop();

	} catch(string &msg) {
		cout << msg << endl;
	}
	return 0;
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 300, 0, 300, -1, 1);
}


void display() {
	GLdouble *pontos = coordenadas.data();
	glClear(GL_COLOR_BUFFER_BIT);
	COLORREF rosa = 0xFF1CAE;
	float m_ColorR = GetRValue(rosa) / 255.0f;
	float m_ColorG = GetGValue(rosa) / 255.0f;
	float m_ColorB = GetBValue(rosa) / 255.0f;
	glColor3f(m_ColorR, m_ColorG, m_ColorB);

	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH_HINT);
	glEnable(GL_POLYGON_STIPPLE);
	if(!preenchimento) {
		glLineWidth(3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	glPolygonStipple(dog_map);
	glPushAttrib(GL_POLYGON_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_DOUBLE, 0, pontos);
	glDrawArrays(GL_POLYGON, 0, coordenadas.size() / 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_POLYGON_SMOOTH_HINT);
	glDisable(GL_POLYGON_SMOOTH);
	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 27: exit(0);
		default: break;
	}
}
