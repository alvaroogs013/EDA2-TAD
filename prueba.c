#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dispersion.h"
#include <sys/types.h>

int main()
{
    int hashCreado;
    tipoAlumno alumno;
    regConfig config = {15, 4, 0, 75, 40, 0,0};
    int errcode;


    //Ejercicio 1 

    errcode = creaHash("alumnos.dat", "alumnos.hash", &config);
    // printf("Resultado de la función creaHash: %d\n", &result);
    //printf("Número de registros en el archivo hash: %d\n", config.numReg);
    //printf("Número de registros desbordados: %d\n", config.numRegDes);

    errcode = leeHash("alumnos.hash");
    printf("\n\n%d\n",errcode);
    

    // Prueba de la función busquedaHash
    // FILE *f = fopen("alumnosC.hash", "rb");
    // int nCubo, nCuboDes, posReg, error;
    // tipoAlumno *alumno = busquedaHash(f, "12345678A", &nCubo, &nCuboDes, &posReg, &error);
    // printf("\nResultado de la función busquedaHash:\n");
    // if (error == 0) {
    //     printf("Registro encontrado en el cubo %d", nCubo);
    //     if (nCuboDes != -1) {
    //         printf(" y en el cubo desbordado %d", nCuboDes);
    //     }
    //     printf(" en la posición %d\n", posReg);
    //     printf("DNI: %s\n", alumno->dni);
    //     printf("Nombre: %s\n", alumno->nombre);
    //     printf("Provincia: %s\n", alumno->provincia);
    // } else if (error == -1) {
    //     printf("Registro no encontrado\n");
    // } else if (error == -2) {
    //     printf("Problemas con el fichero de datos\n");
    // } else if (error == -4) {
    //     printf("Otro error en el proceso\n");
    // }
    // fclose(f);

    // Prueba de la función modificarReg
    // int result_mod = modificarReg("alumnosC.hash", "12345678A", "Barcelona");
    // printf("\nResultado de la función modificarReg: %d\n", result_mod);

    // return 0;
    
    
}

