#include <utility>
#include <windows.h>
#include <GL\glut.h>
#include <list>
#include <fstream>
#include <iostream>

using namespace std;

list<pair<double, double>> coordenadas;

void init();

void display();

void keyboard(unsigned char key, int x, int y);

pair<double, double> split(string line, const string &delimiter);

void lerArquivo();

int main(int argc, char **argv) {
	lerArquivo();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Desenhando uma linha");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void lerArquivo() {
	ifstream arquivo;
	string linha;
	
	arquivo.open("arquivo.txt", ios_base::in);
	if (arquivo.is_open()) {
		while (!arquivo.eof()) {
			getline(arquivo, linha);
			coordenadas.push_back(split(linha, ","));
		}
	}
}

pair<double, double> split(string line, const string &delimiter) {
	string aux = std::move(line);
	size_t pos = aux.find(delimiter);
	pair<double, double> results(stod(aux.substr(0, pos)), stod(aux.substr(
			pos + 1, aux.size() - 1)));
	return results;
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, 300, 0, 300, -1, 1);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	
	for (pair<double, double> coordenada: coordenadas) {
		
		glBegin(GL_LINES);
		glVertex2i(static_cast<GLint>(coordenada.first), static_cast<GLint>(coordenada.second));
		glEnd();
		
	}
	
	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
		default:
			break;
	}
}
