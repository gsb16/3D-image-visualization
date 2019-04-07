# Visualização de imagens em 3D

## Gabriel Barreto - GRR20166812

## Objetivos:
Projeto da disciplina ci067 de 2016/2
- Aprendizado e uso de novas bibliotecas; 
- Aplicação da SDL;
- Tratamentos de inputs do teclado e mouse;
- Planejamento e manipulação de structs apropriadas;

## Compilação:
O Makefile faz ligação automática com as bibliotecas
- *make:* compilação do código e criação do executável "wireframe"
- *make purge:* deleta o executável

## Execução:
- Requer uma imagem em arquivo obj
```
./wireframe < inputfile.obj
```
 
## Bugs conhecidos:
- Pelo uso de perspectiva fraca, a imagem fica distorcida em rotações grandes

## Implementação pendente:
- Perspectiva forte
- Uso do mouse para zoom in e out
