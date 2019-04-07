
// GRR 20166812 -- Gabriel de Souza Barreto

#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>

#include "objread.h"

FILE *arq;

int largu = 800, altu = 600;
solido_t solido;
vertice_t vertice, camera;
face_t face;
vertimag_t vertimag, *projec, *desenho;
escala_t escala;
SDL_Surface* screen = NULL;

int main(int argc, char const *argv[])
{
	//checa se precisa abrir um arquivo
	if (argc == 2)
	{
		arq = fopen(argv[1], "r");
		if (!arq)
		{
			printf("Arquivo nao encontrado\n");
			exit(1);
		}
	}
	else
	{
		arq = fopen(".wiretemp", "w+");
		
		char letra;
		
		do
		{
			letra = fgetc(stdin);
			fputc(letra, arq);
		} while(letra != EOF);
		rewind (arq);
		//arq = stdin;
	}


	//inicializa a camera
	camera.coordx = 0;
	camera.coordy = 0;
	camera.coordz = 5000;

	leituraobj(arq, &solido);
	SDL_Init( SDL_INIT_EVERYTHING ); 
	screen = SDL_SetVideoMode( largu, altu, 32, SDL_SWSURFACE );

	projec = (vertimag_t*) malloc((solido.tamvert + 1) * sizeof(vertimag_t));
	desenho = (vertimag_t*) malloc((solido.tamvert + 1) * sizeof(vertimag_t));

	SDL_Event evento;

	bool mouse = false;

	//Remove o arquivo temporario criado
	if (argc != 2)
	{
		remove(".wiretemp");
	}

	while (1)
	{
		while (SDL_PollEvent(&evento))
		{
			switch (evento.type)
			{
				case SDL_QUIT:
					exit (0);
				break;

				
				case SDL_MOUSEBUTTONDOWN:
					if( evento.button.button == SDL_BUTTON_LEFT )
					{
						mouse = true;
					}
				break;

				case SDL_MOUSEBUTTONUP:
					if( evento.button.button == SDL_BUTTON_LEFT )
					{
						mouse = false;
					}
				break;

				case SDL_MOUSEMOTION:
					if (mouse == true)
					{
						camera.coordx += 10.0 * evento.motion.xrel;
						camera.coordy += 10.0 * evento.motion.yrel;
					}
				break;

				case SDL_KEYDOWN:
					switch (evento.key.keysym.sym)
					{
						case SDLK_UP:
							camera.coordy += 100;
						break;

						case SDLK_DOWN:
							camera.coordy -= 100;
						break;

						case SDLK_RIGHT:
							camera.coordx += 100;
						break;

						case SDLK_LEFT:
							camera.coordx -= 100;
						break;

						case SDLK_w:
							camera.coordz -= 50;
						break;

						case SDLK_s:
							camera.coordz += 50;
						break;

						default:
						break;	
					}
				break;
				
				default:
				break;
			}
		}
		
		perspectiva_fraca (solido, projec, camera);
		
		if (escala.escala == 0)
			escala = escala2d(solido, largu, altu, projec);
		
		pontplot (solido, escala, projec, desenho, largu, altu);

		
		//printf("%d\n", solido.tamface); TESTE

		SDL_FillRect(screen, NULL, 0x000000);

		for (int j = 1; j <= solido.tamface; ++j)
		{
			for (int k = 1; k <= solido.vetorface[j].numvert-1; ++k)
			{
				lineRGBA (screen, desenho[solido.vetorface[j].pontvert[k]].imagx, desenho[solido.vetorface[j].pontvert[k]].imagy,
				 desenho[solido.vetorface[j].pontvert[k+1]].imagx, desenho[solido.vetorface[j].pontvert[k+1]].imagy, 255, 255, 255, 42);

				//printf("%f %f %f %f\n",desenho[solido.vetorface[j].pontvert[k]].imagx, desenho[solido.vetorface[j].pontvert[k]].imagy,
				 //desenho[solido.vetorface[j].pontvert[k+1]].imagx, desenho[solido.vetorface[j].pontvert[k+1]].imagy); TESTE
			}
			lineRGBA (screen, desenho[solido.vetorface[j].pontvert[1]].imagx, desenho[solido.vetorface[j].pontvert[1]].imagy,
				 desenho[solido.vetorface[j].pontvert[solido.vetorface[j].numvert]].imagx, desenho[solido.vetorface[j].pontvert[solido.vetorface[j].numvert]].imagy, 255, 255, 255, 42);

			//printf("%f %f %f %f\n",desenho[solido.vetorface[j].pontvert[1]].imagx, desenho[solido.vetorface[j].pontvert[1]].imagy,
				 //desenho[solido.vetorface[j].pontvert[solido.vetorface[j].numvert]].imagx, desenho[solido.vetorface[j].pontvert[solido.vetorface[j].numvert]].imagy); TESTE
		}

		
		SDL_Flip( screen );
	}

	SDL_Delay( 10000 );

	SDL_Quit();  
	
	
	return(0);
}

