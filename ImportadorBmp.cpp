//
// Created by YanAL on 11/03/2019.
//

#include <fstream>
#include "ImportadorBmp.h"

/**
 * Construtor principal da classe Utils para importar imagem BMP
 * @param nomeArquivo
 */
ImportadorBmp::ImportadorBmp(const char *nomeArquivo) {
	try {
		FILE *arquivo = fopen(nomeArquivo, "rb");
		if (!arquivo) {
			throw string("Arquivo não foi aberto.");
		}
		fread(&bfh, sizeof(BITMAPFILEHEADER), 1, arquivo);
		if (bfh.bfType != 0x4D42) {
			throw string("Imagem inválida");
		}
		fread(&bih, sizeof(BITMAPINFOHEADER), 1, arquivo);
		if (bih.biSizeImage == 0) {
			bih.biSizeImage = static_cast<DWORD>(bih.biHeight * bih.biWidth);
		}
		textura = new unsigned char[bih.biSizeImage];
		fseek(arquivo, bfh.bfOffBits, SEEK_SET);
		fread(textura, 1, bih.biSizeImage, arquivo);
		for (int i = 0; i < bih.biSizeImage; i += 3) {
			swap(textura[i], textura[i + 2]);
		}
		largura = bih.biWidth;
		altura = bih.biHeight;
		fclose(arquivo);
	} catch (string &msg) {
		throw string(msg);
	}
}

ImportadorBmp::~ImportadorBmp() {
	delete[] textura;
}
