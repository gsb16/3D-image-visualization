
# GRR 20166812 -- Gabriel de Souza Barreto

CFLAGS = -Wall -lSDL -lSDL_gfx -lm

wireframe: wireframe.c proje.c objread.c objread.h
	gcc wireframe.c proje.c objread.c -o wireframe $(CFLAGS)

purge: clean
	-rm wireframe 