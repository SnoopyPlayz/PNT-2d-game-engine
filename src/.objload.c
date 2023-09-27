#include <GL/glew.h>
#include <cglm/cglm.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/*!!! DEAD CODE !!!   !!! DEAD CODE !!!   !!! DEAD CODE !!!*/

void saveInds(int * data, int num, char readline[100], char * type){
        int x,y,z,a = 0;
        char indsFormat[100];
        sprintf(indsFormat, "%%*c %s %s %s %s", type, type, type, type);

        sscanf(readline, indsFormat, &x, &y, &z, &a);

        data[num] = x - 1; //Triangle 1
        data[num+1] = y - 1;
        data[num+2] = z - 1;

        if (!a) // is there another triangle
                return;

        data[num+3] = x - 1; //Triangle 2
        data[num+4] = z - 1;
        data[num+5] = a - 1;
}

int findInArray(float * array,int arSize, Tex tex, Pos pos){
        for (int i = 0; i < arSize; i++){
                Pos arPos;
                arPos.pX = array[i];
                arPos.pY = array[i+1];
                arPos.pZ = array[i+2];
                Tex arTex;
                arTex.tX = array[i+3];
                arTex.tY = array[i+4];

                if (arPos.pX == pos.pX && arPos.pY == pos.pY && arPos.pZ == pos.pZ &&
                                arTex.tX == tex.tX && arTex.tY == tex.tY){
                        return i;
                }
        }
        return -1;
}


Model loadObj(char * filePath){
        FILE * objFile = fopen(filePath,"r");

        if (!objFile){
                printf("NO OBJ FILE %s \n",filePath);
                return (Model) {};
        }

        char readline[100];
        int numVert = 0, numInds = 0, numTex = 0;

        while (fgets(readline, 100, objFile)){ //How many inds
                if (!strncmp(readline, "v ", 2))
                        numVert += 1;

                if (!strncmp(readline, "vt", 2))
                        numTex += 1;

                if (readline[0] == 'f')
                        numInds += 1;
        }
        Pos vert[numVert];
        int verInds[numInds*6];

        Tex tex[numTex];
        int texInds[numInds*6];

        fseek(objFile,0,SEEK_SET);

        numVert = 0; numInds = 0; numTex = 0; 
        while (fgets(readline, 100, objFile)){ //Load inds
                if(!strncmp(readline, "v ", 2)){
                        sscanf(readline,"%*c %f %f %f",
                                &vert[numVert].pX, &vert[numVert].pY, &vert[numVert].pZ);

                        numVert++;
                }
                if(!strncmp(readline, "vt", 2)){
                        sscanf(readline,"%*c%*c %f %f",
                                &tex[numTex].tX, &tex[numTex].tY);
                        numTex++;
                }
                if(readline[0] == 'f'){

                        saveInds(verInds, numInds, readline, "%d/%*d/%*d");
                        saveInds(texInds, numInds, readline, "%*d/%d/%*d");
                        numInds+=6;
                }
        };
        fclose(objFile);

        int newVertSize = (numTex + numVert)*2;
        float newVert[newVertSize];
        int newInds[(numInds+ numInds)*2];
        for (int i = 0; i < numInds/6; i++){

                int t = findInArray(newVert,
                                newVertSize,
                                tex[texInds[i]], vert[verInds[i]]);
                if (t == -1){
                        newVert[i] = vert[verInds[i]].pX;
                        newVert[i+1] = vert[verInds[i]].pY;
                        newVert[i+2] = vert[verInds[i]].pZ;

                        newVert[i+3] = tex[texInds[i]].tX;
                        newVert[i+4] = tex[texInds[i]].tY;

                        newInds[i] = i;
                }else {
                        newInds[i] = t;
                }
                int e = newInds[i];
                printf("%f %f %f", newVert[e], newVert[e+1], newVert[e+2]);
                printf(" %f %f \n", newVert[e+3], newVert[e+4]);
        }

        return bufferModel(newVert, newInds, sizeof(newVert), sizeof(newVertSize));
}
