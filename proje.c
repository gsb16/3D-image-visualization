
// GRR 20166812 -- Gabriel de Souza Barreto

#include <stdio.h>
#include "objread.h"

void perspectiva_fraca (solido_t solido, vertimag_t *projec, vertice_t camera)
{

	for (int i = 1; i <= solido.tamvert; i++)
	{
		// MALLOC! MALLOC! MALLOC!
		projec[i].imagx = camera.coordx + camera.coordz * ((solido.vetorvert[i].coordx - camera.coordx) * 1.0 / (solido.vetorvert[i].coordz + camera.coordz));
		projec[i].imagy = camera.coordy + camera.coordz * ((solido.vetorvert[i].coordy - camera.coordy) * 1.0 / (solido.vetorvert[i].coordz + camera.coordz));
	}
}

escala_t escala2d (solido_t solido, int largu, int altu, vertimag_t *projec)
{
	vertimag_t mini, maxi;
	escala_t escala;
	float escx, escy;

	mini.imagx = mini.imagy = 1e7;
	maxi.imagx = maxi.imagy = -1;

	for (int i = 1; i <= solido.tamvert; ++i)
	{
		if (projec[i].imagx < mini.imagx)
		{
			mini.imagx = projec[i].imagx;
		}
		if (projec[i].imagy < mini.imagy)
		{
			mini.imagy = projec[i].imagy;
		}
		if (projec[i].imagx > maxi.imagx)
		{
			maxi.imagx = projec[i].imagx;
		}
		if (projec[i].imagy > maxi.imagy)
		{
			maxi.imagy = projec[i].imagy;
		}
	}

	escala.centro.imagx = (maxi.imagx + mini.imagx) / 2.0;
	escala.centro.imagy = (maxi.imagy + mini.imagy) / 2.0;

	escx = largu / (maxi.imagx - mini.imagx);
	escy = altu / (maxi.imagy - mini.imagy);

	if (escx > escy)
	{
		escala.escala = escy; 
	}
	else
	{
		escala.escala = escx;
	}

	//escala.centro.imagx *= escala.escala;
	//escala.centro.imagy *= escala.escala;

	return (escala);

}

void pontplot (solido_t solido, escala_t escala, vertimag_t *projec, vertimag_t *desenho, int largu, int altu)
{

	for (int i = 1; i <= solido.tamvert; i++)
	{
		desenho[i].imagx = ((projec[i].imagx - escala.centro.imagx) * escala.escala) + largu / 2.0;
		desenho[i].imagy = altu -(((projec[i].imagy - escala.centro.imagy) * escala.escala) + altu / 2.0);
	}
}