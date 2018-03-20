//
//  manager.c
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
#include <signal.h>


#define LECTURA 0
#define ESCRITURA 1
#define MAX_BUF 32
pid_t pid[2];
//Manejador de la interrupcion.
void manejador(int dummy){
    //Matamos los procesos abiertos B y C.
    for(int i =0;i<2;i++)
        kill(pid[0], SIGKILL);
    //Ejecutamos el proceso PD para la limpieza.
    system("ps");
    execv("./PD",NULL);
}

int main (int argc, char** argv){
    int i,estado,fd;
    FILE *log;
    char cadena[MAX_BUF];
    char buffer[MAX_BUF];
    int tuberia[2];
    system("ps");
  
    //Control del manejador
    signal(SIGINT,manejador);
    //Creacion del archivo log.
    if((log=fopen("log.txt","w"))== NULL){
        fprintf(stderr, "[MANAGER] Error al crear el archivo log\n");
        exit(EXIT_FAILURE);
    }
    fprintf(log,"******** Log del sistema ******** \n");
    
    //Ejecución del proceso A.
    switch (pid[1]=fork()) {
        case -1:
            fprintf(stderr,"[MANAGER] Error al crear el proceso A\n");
            break;
        case 0:
            execv("./PA",NULL);
            printf("[MANAGER] Error al ejecutar el proceso hijo A \n");
        break;
        default:
            printf("[MANAGER] Esperando al proceso A... \n");
        break;
    }
    
    //Esperamos a que termine el proceso A y comenzamos la ejecución de los otros dos procesos.
    waitpid(pid[1],&estado,0);
    if(estado ==0){
        printf("[MANAGER] El proceso A ha finalizado\n");
        fprintf(log,"Creación de directorios finalizada.\n");
        
        
        pipe(tuberia);
        //CREACION DE LOS PROCESOS PC Y PB
        for(i=0;i<2;i++){
            switch (pid[i]=fork()) {
                case -1:
                    fprintf(stderr,"[MANAGER] Error al crear el proceso %d\n",i);
                    break;
                case 0:
                    if(i==0){
                        execv("./PB",NULL);
                        printf("[MANAGER] Error al ejecutar el proceso hijo B\n");
                    }else if(i==1){
                        dup2(tuberia[ESCRITURA],STDOUT_FILENO);
                        execv("./PC",NULL);
                        printf("[MANAGER] Error al ejecutar el proceso hijo C\n");
                    }
                    break;
                default:
                    if(i==0)
                        printf("[MANAGER] Esperando al proceso B... \n");
                    else
                        printf("[MANAGER] Esperando al proceso C... \n");
                    break;
            }
        }
        
        //Esperamos a que los dos procesos terminen.
        for(i=0;i<2;i++){
            if(i==0){
                pid[i] = wait(NULL);
                printf("[MANAGER] El proceso B ha finalizado\n");
                fprintf(log,"Copia de modelos de examen, finalizada.\n");
            }else if(i==1){
                pid[i]=wait(NULL);
                read(tuberia[LECTURA],buffer,sizeof(buffer));
                //printf("[MANAGER] %s\n",buffer);
                printf("[MANAGER] El proceso C ha finalizado\n");
                fprintf(log,"Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n");
                fprintf(log,"%s\n",buffer);
            }
        }
    }
    fprintf(log,"FIN DEL PROGRAMA \n");
    return EXIT_SUCCESS;
}

