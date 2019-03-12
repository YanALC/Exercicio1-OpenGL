//
// Created by YanAL on 11/03/2019.
//

#ifndef OPENGL_TESTE_BMPIMPORTER_H
#define OPENGL_TESTE_BMPIMPORTER_H

#include <windows.h>
#include <iostream>

using namespace std;

/**
 * @class ImportadorBmp
 * Utils para importar imagens BMP como textura no OpenGL
 */
class ImportadorBmp {
public:
	unsigned char *textura = nullptr;
	int largura{}, altura{};
	
	ImportadorBmp() = default;
	
	explicit ImportadorBmp(const char *nomeArquivo);
	
	~ImportadorBmp();

private:
	BITMAPFILEHEADER bfh{};
	BITMAPINFOHEADER bih{};
};


#endif //OPENGL_TESTE_BMPIMPORTER_H
