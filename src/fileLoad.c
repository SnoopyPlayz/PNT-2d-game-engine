#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// TEXTURE			TEXTURE

unsigned int loadTexture(char* fileLocation) {
	stbi_set_flip_vertically_on_load(1);

 	int width, height, nrChannels;
 	unsigned char *data = stbi_load(fileLocation, &width, &height, &nrChannels, 0);
	 
 	if (!data){
 		printf("error loading image file: %s",fileLocation);
 		return 0;
 	}
	 
	unsigned int texture;
	glGenBuffers(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);
	return texture;
}

// PLY MODEL LOADING			PLY MODEL LOADING

typedef struct Model {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	int numIndices;
} Model;

Model bufferModel(float * vert, int * inds, int vertSize, int indsSize){
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
 
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertSize, vert, GL_STATIC_DRAW);
 
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsSize, inds, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	return (Model) {VAO,VBO,EBO,indsSize};
}

void saveInds(int * inds, int indsPos, char readline[100]){
	int x,y,z,a;

	sscanf(readline, "%*d %d %d %d %d", &x, &y, &z, &a);

	inds[indsPos] = x; //Triangle 1
	inds[indsPos+1] = y;
	inds[indsPos+2] = z;

	if (!a) // is there another triangle
		return;
	
	inds[indsPos+3] = x; //Triangle 2
	inds[indsPos+4] = z;
	inds[indsPos+5] = a;
}

void saveVerts(float * V, int vertPos, char readline[100]){
	sscanf(readline, "%f %f %f %f %f %f %f %f",
			&V[vertPos],&V[vertPos+1],&V[vertPos+2],&V[vertPos+3],
			&V[vertPos+4],&V[vertPos+5],&V[vertPos+6],&V[vertPos+7]);
}

Model loadModel(char * filePath){
        FILE * modelFile = fopen(filePath,"r");
	
        if (!modelFile){
		printf("NO MODEL FILE %s \n",filePath);
		return (Model) {};
	}

        char readline[100];
	int numVert = 1, numInds = 1;

        while (fgets(readline, 100, modelFile)){ // Model metadata

		if(!strncmp(readline, "element vertex", 14)){
			sscanf(readline,"%*s %*s %d", &numVert);
		}
		if(!strncmp(readline, "element face", 12)){
			sscanf(readline,"%*s %*s %d", &numInds);
		}
		if(!strncmp(readline, "end_header", 10)){
			break;
		}
	}

	printf("%d \n", numVert);
	printf("%d \n", numInds);
	float vert[numVert * 8];
	int inds[numInds * 6];

	for (int i = 0; i < numVert*8; i+=8){ // Load Vertex and Index data
		fgets(readline, 100, modelFile);
		saveVerts(vert, i, readline);
	}
	
	for (int i = 0; i < numInds*6; i+=6){
		fgets(readline, 100, modelFile);
		saveInds(inds, i, readline);
	}

	return bufferModel(vert, inds, sizeof(vert), sizeof(inds));
}

