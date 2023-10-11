#pragma once
typedef struct Texture{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	int numIndices;
	unsigned int texture;
	int width;
	int height;
	int screenSizeChange; //monitor Width + height
} Texture;
Texture loadImage2d(char * fileLocation, int x, int y);
