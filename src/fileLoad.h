#pragma once
typedef struct Texture{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	int numIndices;
	unsigned int texture;
	int width;
	int height;
	int x;
	int y;
	float z;
} Texture;
//width = 0  auto
//height = 0  auto
Texture loadImage2d(char * fileLocation, int x, int y);
Texture loadStrechedImage(char * fileLocation, int width, int height, int x, int y);
