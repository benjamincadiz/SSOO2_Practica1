//
//  PD.c
//  
//
//  Created by Benjamin Cadiz de Gracia on 27/2/18.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main (int argc, char**argv){
    FILE *log;
    
    if((log=fopen("log.txt","w"))== NULL){
        fprintf(stderr, "[MANAGER] Error al crear el archivo log\n");
        exit(EXIT_FAILURE);
    }
    //Comprobacion de la carpeta alumnos para limpiarla de todo el contenido.
    if(fopen("Alumnos/","rwx")){
        system("rm -rf Alumnos/");
        printf("[PD] Carpeta borrada correctamente\n");
    }
    fprintf(log,"********  Programa interrumpido voluntariamente *****");
    return EXIT_SUCCESS;
}
