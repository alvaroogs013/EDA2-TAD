# Practica TAD
prueba:prueba.c dispersion.o  
	gcc -g prueba.c dispersion.o indice.o -o prueba
dispersion.o: dispersion.h dispersion.c
	gcc -c -g dispersion.c
indice.o: indice.h indice.c
	gcc -c -g indice.c

