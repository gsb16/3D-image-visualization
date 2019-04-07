
// GRR 20166812 -- Gabriel de Souza Barreto

#include <stdio.h>
#include <stdlib.h>


typedef struct vertice_t
{
	float coordx;
	float coordy;
	float coordz;
} vertice_t;

typedef struct face_t
{
	int numvert;
	int *pontvert;
	
} face_t;

typedef struct solido_t
{
	int tamvert;
	vertice_t *vetorvert;
	int tamface;
	face_t *vetorface;
} solido_t;

typedef struct vertimag_t
{
	float imagx;
	float imagy;	
} vertimag_t;

typedef struct escala_t
{
	vertimag_t centro;
	float escala;
} escala_t;



void leituraobj(FILE *arq, solido_t *solido);

void perspectiva_fraca (solido_t solido, vertimag_t *projec, vertice_t camera);

escala_t escala2d (solido_t solido, int largu, int altu, vertimag_t *projec);

void pontplot (solido_t solido, escala_t escala, vertimag_t *projec, vertimag_t *desenho, int largu, int altu);