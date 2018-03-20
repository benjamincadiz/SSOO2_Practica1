//
//  PC.c
//
//
//  Created by Benjamin Cadiz de Gracia on 20/2/18.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 32

int main (int argc, char** argv){
    FILE *students,*note;
    const char *space = " ";
    int count,num_students, src_fd, dst_fd,nota_f,sum_nota;
    num_students=0;
    sum_nota=0;
    double nota_media;
    char* line = NULL;
    ssize_t read;
    size_t len =0;
    char *token;
    char *dni;
    char *modelo;
    char *nota;
    char ruta_f[50],notaa[50],str[20],buffer[MAX_BUF];
    
    students = fopen("Estudiantes.txt","r");
    if(students==NULL){
        fprintf(stderr, "[PC] Error en la lectura del archivo\n");
        return EXIT_FAILURE;
    }else{
        while ((read = getline(&line, &len, students)) != -1) {
            count =0;
            num_students++;
            for (token = strtok(line, space); token; token = strtok(NULL, space)){
                strcpy(ruta_f,"");
                strcpy(notaa,"");
                strcpy(str,"");
                //printf("Count \n");
                switch (count) {
                    case 0:
                        dni = token;
                        break;
                    case 1:
                        modelo = token;
                        break;
                    case 2:
                        strcpy(ruta_f,"Alumnos/");
                        strcat(ruta_f,dni);
                        strcat(ruta_f,"/nota.txt");
                        nota = token;
                        sum_nota+=atoi(nota);
                        //printf("Nota media %d\n",sum_nota);
                        nota_f = 10 - atoi(nota);
                        note = fopen(ruta_f,"w");
                        if(note == NULL){
                            fprintf(stderr,"[PC] No se ha podido crear el fichero\n");
                            exit(EXIT_FAILURE);
                        }else{
                            strcpy(notaa, " La nota necesaria para aprobar es : ");
                            sprintf(str,"%d",nota_f);
                            strcat(notaa,str);
                            fprintf(note,"%s",notaa);
                            fclose(note);
                        }
                    
                }
                count++;
                }
            }
        nota_media = (double)sum_nota/(double)num_students;
        printf("La nota media de la clase es : %f",nota_media);
        fclose(students);
    }
    return EXIT_SUCCESS;
}

