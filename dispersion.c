#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lee el contenido del fichero hash organizado mediante el método de DISPERSIÓN según los criterios
// especificados en la práctica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta función permite visualizar el método de DISPERSIÓN

int leeHash(char *fichHash)
{ FILE *f;
  tipoCubo cubo;
  regConfig regC;
  int j,nCubo=0,densidadOcupacion;

   f = fopen(fichHash,"rb");
   fread(&regC,sizeof(regConfig),1,f);
   fread(&cubo,sizeof(cubo),1,f); 
   while (!feof(f)){
	for (j=0;j<C;j++) {
        	if (j==0) printf("Cubo %2d (%2d reg. ASIGNADOS)",nCubo,cubo.numRegAsignados);
        	else 	if ((j==1) && cubo.desbordado) printf("DESBORDADO\t\t");
        		else printf("\t\t\t");
		if (j < cubo.numRegAsignados) 
		    printf("\t%s %s %s %s %s\n",cubo.reg[j].dni, cubo.reg[j].nombre,cubo.reg[j].ape1,cubo.reg[j].ape2,
			    		cubo.reg[j].provincia);
	    	else printf ("\n");
        	}
		nCubo++;
       fread(&cubo,sizeof(cubo),1,f);
   }
   fclose(f);
   printf("ORGANIZACIÓN MÉTODO DISPERSIÓN:\n\t %d CUBOS y %d CUBOS DESBORDE con capacidad %d\n",
   		regC.nCubos,regC.nCubosDes, C);   
   printf("\t Contiene %d registros de los cuales se han desbordado %d:\n",regC.numReg,regC.numRegDes);
   densidadOcupacion = 100*regC.numReg/((regC.nCubos+regC.nCubosDes)*C);
   printf("Densidad ACTUAL de ocupación: %d \n\t(MÍNIMA permitida %d  MÁXIMA permitida %d)\n",
   				densidadOcupacion,regC.densidadMin,regC.densidadMax);
   if (densidadOcupacion>regC.densidadMax) {
   	printf("No se respeta la densidad máxima de ocupacion\n");
   	return -3;
   }	
   if (densidadOcupacion<regC.densidadMin) {
   	printf("No se respeta la densidad mínima de ocupacion\n");
   	return -4;
   }	
   if ((densidadOcupacion > regC.densidadMin) && (densidadOcupacion < regC.densidadMax))
      	return 0;
   
   return -1;	
}

// FUNCIONES EJERCICIO 1 
void creaHvacio(char *fichHash, regConfig *regC) {
    int i;
    tipoCubo cuboVacio;
    FILE *f;
    int totalCubos = regC->nCubos+regC->nCubosDes;

    memset(&cuboVacio,0,sizeof(cuboVacio));

    // Abrimos el archivo en modo escritura binaria
    f = fopen(fichHash, "wb");
    if (f == NULL) {
        fprintf(stderr, "Error al abrir el archivo %s\n", fichHash);
        exit(EXIT_FAILURE);
    }

    // Escribimos los cubos vacíos
    for (i = 0; i < totalCubos; i++) {
        fwrite(&cuboVacio, sizeof(cuboVacio), 1, f);
    }

    

    // Cerramos el archivo
    fclose(f);
}

int creaHash(char *fichEntrada, char *fichHash, regConfig *regC) {
    
    FILE *fEntrada, *fHash;
    tipoAlumno reg;
    tipoCubo cubo;
    int i, numCubo, k=0;
    int totalCubos = regC->nCubos + regC->nCubosDes;

    creaHvacio(fichHash, regC);
    fEntrada = fopen(fichEntrada,"rb");
    if(NULL == fEntrada){
        printf("\nError al abrir el fichero %s\n", fichEntrada);
        return -1;
    }

    fHash = fopen(fichHash,"r+b");
    if(NULL == fHash){
        printf("\nError al abrir el fichero %s\n", fichHash);
        return -2;
    }

    fread(&reg,sizeof(reg),1,fEntrada);

    while(!feof(fEntrada)){
        numCubo = ((atoi(reg.dni))%regC->nCubos);
        printf("\n\n%d\n\n",numCubo);
        fseek(fHash, numCubo*sizeof(cubo), SEEK_SET);
        fread(&cubo,sizeof(cubo),1,fHash);
        i=cubo.numRegAsignados;
        if(i>=C){

        } else {
            cubo.reg[i] = reg;
            cubo.numRegAsignados++;
            regC->numReg++;

            if (cubo.numRegAsignados == C){
                cubo.desbordado = 1;
                regC->nCuboDesAct++;
            }
        }

        fseek(fHash, numCubo*sizeof(tipoCubo), SEEK_SET);
        fwrite(&cubo, sizeof(tipoCubo), 1, fHash);

        fread(&reg, sizeof(reg), 1, fEntrada);
    }

    fclose(fEntrada);
    fclose(fHash);
    return 0;
}





// void desborde(FILE *fHash,tipoAlumno *reg, regConfig *regC) {
//     int cubo_desborde = regC->nCuboDesAct;
//     tipoCubo cubo;

//     // Leer el cubo de desborde actual
//     fseek(fHash, (regC->nCubos + cubo_desborde) * sizeof(tipoCubo), SEEK_SET);
//     fread(&cubo, sizeof(tipoCubo), 1, fHash);

//     // Si el cubo de desborde actual está lleno, buscar el siguiente cubo disponible
//     while (cubo.numRegAsignados >= C) {
//         cubo_desborde++;
//         if (cubo_desborde >= regC->nCubosDes) {
//             // No hay más cubos de desborde disponibles, añadir uno nuevo
//             regC->nCubosDes++;
//             fseek(fHash, sizeof(regConfig), SEEK_SET);
//             fwrite(&regC->nCubosDes, sizeof(int), 1, fHash);
//             fseek(fHash, (regC->nCubos + regC->nCubosDes - 1) * sizeof(tipoCubo), SEEK_SET);
//             cubo.numRegAsignados = 0;
//             cubo.desbordado = 0;
//             fwrite(&cubo, sizeof(tipoCubo), 1, fHash);
//         } else {
//             // Leer el siguiente cubo de desborde
//             fseek(fHash, (regC->nCubos + cubo_desborde) * sizeof(tipoCubo), SEEK_SET);
//             fread(&cubo, sizeof(tipoCubo), 1, fHash);
//         }
//     }

//     // Añadir el registro al cubo de desborde actual
//     cubo.reg[cubo.numRegAsignados] = *reg;
//     cubo.numRegAsignados++;

//     // Si el cubo de desborde actual está lleno, marcarlo como desbordado y actualizar el valor de nCuboDesAct
//     if (cubo.numRegAsignados >= C) {
//         cubo.desbordado = 1;
//         regC->nCuboDesAct = cubo_desborde + 1;
//     }

//     // Escribir el cubo de desborde actual en el archivo de hash
//     fseek(fHash, (regC->nCubos + cubo_desborde) * sizeof(tipoCubo), SEEK_SET);
//     fwrite(&cubo, sizeof(tipoCubo), 1, fHash);

//     // Actualizar el número de registros desbordados en el registro de configuración
//     regC->numRegDes++;
//     fseek(fHash, 0, SEEK_SET);
//     fwrite(regC, sizeof(regConfig), 1, fHash);
// }

// // FUNCIONES EJERCICIO 2

// tipoAlumno *busquedaHash(FILE *f, char *dni, int *nCubo, int *nCuboDes, int *posReg, int *error) {
//     tipoCubo cubo;
//     tipoAlumno *alumno = NULL;
//     int nCubos = 0;
//     int nCubosDes = 0;
//     int encontrado = 0;
//     int posEnCubo = -1;
//     int i, j;
    
//     // Comprobar que el fichero de datos está abierto correctamente
//     if (f == NULL) {
//         *error = -2;
//         return NULL;
//     }
    
//     // Buscar el registro en los cubos principales
//     fseek(f, 0, SEEK_SET);
//     for (i = 0; i < *nCubo; i++) {
//         fread(&cubo, sizeof(tipoCubo), 1, f);
//         if (cubo.numRegAsignados > 0) {
//             for (j = 0; j < C; j++) {
//                 if (strcmp(cubo.reg[j].dni, dni) == 0) {
//                     encontrado = 1;
//                     posEnCubo = j;
//                     break;
//                 }
//             }
//             if (encontrado) {
//                 alumno = &cubo.reg[posEnCubo];
//                 *nCubo = i;
//                 *nCuboDes = -1;
//                 *posReg = posEnCubo;
//                 *error = 0;
//                 return alumno;
//             }
//         }
//     }
    
//     // Buscar el registro en los cubos de desbordamiento
//     fseek(f, sizeof(tipoCubo), SEEK_SET);
//     for (i = 0; i < *nCuboDes; i++) {
//         fread(&cubo, sizeof(tipoCubo), 1, f);
//         if (cubo.numRegAsignados > 0) {
//             for (j = 0; j < C; j++) {
//                 if (strcmp(cubo.reg[j].dni, dni) == 0) {
//                     encontrado = 1;
//                     posEnCubo = j;
//                     break;
//                 }
//             }
//             if (encontrado) {
//                 alumno = &cubo.reg[posEnCubo];
//                 *nCubo = *nCubo + i;
//                 *nCuboDes = cubo.desbordado;
//                 *posReg = posEnCubo;
//                 *error = 0;
//                 return alumno;
//             }
//         }
//     }
    
//     // Si el registro no se encuentra, asignar valor de error correspondiente
//     *error = -1;
//     return NULL;
// }

// int modificarReg(char *fichero, char *dni, char *provincia) {
//     FILE *f = fopen(fichero, "r+b");
//     if (f == NULL) {
//         return -2; // Error en el fichero
//     }

//     int nCubo, nCuboDes, posReg, error;
//     tipoAlumno *alumno = busquedaHash(f, dni, &nCubo, &nCuboDes, &posReg, &error);

//     if (alumno == NULL) {
//         fclose(f);
//         return -1; // Registro no encontrado
//     }

//     strcpy(alumno->provincia, provincia);

//     // Escribir el registro modificado en el archivo
//     int offset = (nCubo * 5 + posReg) * sizeof(tipoAlumno);
//     fseek(f, offset, SEEK_SET);
//     fwrite(alumno, sizeof(tipoAlumno), 1, f);

//     fclose(f);

//     return nCubo;
// }



