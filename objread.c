
// GRR 20166812 -- Gabriel de Souza Barreto

#include <stdio.h>
#include "objread.h"

//Le o arquivo obj e grava na estrutura solido
void leituraobj(FILE *arq, solido_t *solido)
{
	char termo;
	int cont, totalv;
	vertice_t vertice;
	face_t face;

	termo = fgetc(arq);
	while (!feof(arq))
	{
		if (termo == 'v')
		{
			termo = fgetc(arq);
			//conta a quantidade de vertices
			if (termo == ' ')
			{
				solido->tamvert++;
				totalv++;
			}
			else
			{
				if ((termo == 't') || (termo == 'n'))
				{
					totalv++;
				}
			}
		}
		else
		{
			if (termo == 'f')
			{
				termo = fgetc(arq);
				//conta a quantidade de faces
				if (termo == ' ')
				{
				solido->tamface++;
				}
			}
		}
		while ((termo != '\n') && (!feof(arq)))
		 	{ 
				//Le o resto da linha
				termo = fgetc(arq);
			}	

		termo = fgetc(arq);
	}
	
	rewind(arq);

	printf("total vertices: %d - vertices validos: %d - faces: %d LIDOS\n", totalv, solido->tamvert, solido->tamface);
	
	//cria os vetores de vertices e de faces do solido
	solido->vetorvert = (vertice_t*) malloc((solido->tamvert + 1)*sizeof(vertice_t));
	solido->vetorface = (face_t*) malloc((solido->tamface + 1)*sizeof(face_t));

	
	solido->tamvert = 1;
	solido->tamface = 1;

	termo = fgetc(arq);
	while (!feof(arq))
	{
		if (termo == 'v')
		{
			termo = fgetc(arq);
			if ((termo == ' ') || (termo == 't') || (termo == 'n'))
			{
				fscanf(arq,"%f %f %f", &vertice.coordx, &vertice.coordy, &vertice.coordz);
				if (termo == ' ')
				{
					//so grava os vertices validos do solido
					solido->vetorvert[solido->tamvert] = vertice;
					//printf("Leu %d vertice valido!\n", solido->tamvert); TESTE
					solido->tamvert++; 
				}			
			}
		}
		
		else
		{
			if (termo == 'f')
			{
				termo = fgetc(arq);
				if (termo == ' ')
				{
					face.numvert = 0;
					cont = 0;


					do
					{
						while (termo == ' ')
						{
							termo = fgetc(arq);
							cont++;
						}
						if (termo != '\n' && termo != '\r' && termo != EOF)
						{
							face.numvert++;
						}
						while (termo != ' ' && termo != '\n' && termo != '\r' && termo != EOF)
						{
							termo = fgetc(arq);
							cont++;
						}
					} while  (termo != '\n' && termo != '\r' && termo != EOF);
					
					
					fseek(arq, -cont, SEEK_CUR);

					//cria um vetor para determinada face
					solido->vetorface[solido->tamface].pontvert = (int*) malloc(face.numvert*sizeof(int));

					//grava os vertices que compoe a face
					for (int i = 1; i <= face.numvert; ++i)
					{
						fscanf(arq,"%d", &solido->vetorface[solido->tamface].pontvert[i]);
						do
						{
							termo = getc(arq);
						} while ((termo != ' ') && (termo != '\n') && (termo != EOF));
					}

					while (termo != '\n'  && (termo != EOF))
					{
						termo = fgetc(arq);
					} 

					solido->vetorface[solido->tamface].numvert = face.numvert;
					//printf("Leu %d face!\n", solido->tamface); TESTE
					solido->tamface++;
				}
			}

			//Le a linha inteira se nao eh vertice nem face
			while (termo != '\n'  && (termo != EOF))
			{ 
				termo = fgetc(arq);
			}	
	
		}
		 
		termo = fgetc(arq);
	}

	//printf("Veio até aqui!\n"); TESTE

	solido->tamvert--;
	solido->tamface--;

	//Teste de todos os vértices e faces lidos
	//for (int i = 1; i <= solido->tamvert; ++i)
	//{
	//	printf("v %f %f %f\n", solido->vetorvert[i].coordx, solido->vetorvert[i].coordy, solido->vetorvert[i].coordz);
	//}
	//
	//printf("\n");
	//
	//for (int i = 1; i <= solido->tamface; ++i)
	//{
	//	printf("f");
	//	for (int j = 1; j <= solido->vetorface[i].numvert; ++j)
	//	{
	//		printf("v%d ", solido->vetorface[i].pontvert[j]);
	//	}
	//	printf("\n");
	//}
}