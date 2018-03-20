//
//  PB.c
//  
//
//  Created by Benjamin Cadiz de Gracia on 19/2/18.
//

#include "PB.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


void copyFile(char* src, char* dest)
{
    unsigned char buffer[4096];
    int src_fd,dst_fd,n,err;
    src_fd = open(src, O_RDONLY);
    dst_fd = open(dest, O_CREAT | O_WRONLY);
    
    while (1) {
        err = read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("[PB] Error reading file.\n");
            exit(EXIT_FAILURE);
        }
        n = err;
        
        if (n == 0) break;
        err = write(dst_fd, buffer, n);
        if (err == -1) {
            printf("[PB] Error writing to file.\n");
            exit(EXIT_FAILURE);
        }
    }
}


int main (int argc, char** argv){
    FILE *students;
    const char *space = " ";
    int count,c, src_fd, dst_fd;
    int alumnos =0;
    count = 0;
    char* line = NULL;
    ssize_t read;
    size_t len =0;
    char *token;
    char *dni;
    char *modelo;
    char *nota;
    char ruta_o[50],ruta_f[50];
    char fichero[50];
  
    students = fopen("Estudiantes.txt","r");
    if(students==NULL){
        fprintf(stderr, "[PB] Error en la lectura del archivo\n");
        return EXIT_FAILURE;
    }else{
        while ((read = getline(&line, &len, students)) != -1) {
            //printf("\n%s", line);
            count =0;
            alumnos++;
            for (token = strtok(line, space); token; token = strtok(NULL, space)){
                strcpy(ruta_f,"");
                strcpy(ruta_o,"");
                switch (count) {
                    case 0:
                        dni = token;
                        break;
                    case 1:
                        //printf("[PB] Hola \n");
                        modelo = token;
                        strcpy(ruta_f,"Alumnos/"); //Copiamos la ruta original para poder modificarlas.
                        strcat(ruta_f,dni);
                        if(strcmp(modelo,"A") == 0){
                            strcpy(ruta_o, "A.pdf");
                            strcat(ruta_f,"/A.pdf");
                            copyFile(ruta_o,ruta_f);
                            chmod(ruta_f,0644);
                        } else if (strcmp(modelo, "B") == 0){
                            strcpy(ruta_o, "B.pdf");
                            strcat(ruta_f,"/B.pdf");
                            copyFile(ruta_o,ruta_f);
                            chmod(ruta_f,0644);
                        }else if (strcmp(modelo, "C")==0){
                            strcpy(ruta_o, "C.pdf");
                            strcat(ruta_f,"/C.pdf");
                            copyFile(ruta_o,ruta_f);
                            chmod(ruta_f,0644);
                        }
                        break;
                    case 2:
                        nota = token;
                        //printf("%s\n",nota);
                        break;
                }
                count++;
            }

        }
        fclose(students);
    }
    return EXIT_SUCCESS;
}
