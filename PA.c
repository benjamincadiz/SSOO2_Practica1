//
//  Practica1.c
//  
//
//  Created by Benjamin Cadiz de Gracia on 15/2/18.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


int main (int argc, char** argv){
    FILE *students;
    const char *space = " ";
    int count,c;
    count = 0;
    char* line = NULL;
    ssize_t read;
    size_t len =0;
    char *dni;
    char ruta[50];
    char fichero[50];
    //Variables de la tuberia.
    int descr, longmens, i;
    char mensaje[100];
    
    //Comprobacion de la carpeta alumnos para limpiarla de todo el contenido.
    if(fopen("Alumnos/","rwx")){
        system("rm -rf Alumnos/");
    }
    //printf("Introduce el archivo que contiene los alumunos:");
    //scanf("%s",fichero);
    students = fopen("Estudiantes.txt","r");
    
    if(students==NULL){
        fprintf(stderr, "Error en la lectura del archivo\n");
        return EXIT_FAILURE;
    }else{
        if(mkdir("Alumnos/",0777)==-1){
            fprintf(stderr, "Error en la creacion de la carpeta\n");
            exit(EXIT_FAILURE);
        }else{
            while ((read = getline(&line, &len, students)) != -1) {
                //printf("\n%s", line);
                dni = strtok(line, space);
                if(dni != NULL) {
                    strcpy(ruta, "Alumnos/");
                    //printf("\nSe ha creado una carpeta para: %s",dni);
                    strcat(ruta,dni);
                    mkdir(ruta,0755);
                    dni = strtok( NULL,  space);
                }
            }
            fclose(students);
        }
    }
    return EXIT_SUCCESS;
}

