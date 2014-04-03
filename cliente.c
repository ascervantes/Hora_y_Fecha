#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
int main(int args, char *argv[]) {

u_int port;
int server;
int client;
int localerror;
struct sockaddr_in server_addr;
socklen_t clienteLen;	
int status;
char *cadena;

    //Validamos los Arguemntos
if(args < 3) {
fprintf(stderr,"Error: Missing Arguments\n");
fprintf(stderr,"\tUSE: %s [ADDR] [PORT]\n",argv[0]);
return 1;
}

//Iniciamos la apertura del Socket
server = socket(PF_INET,SOCK_STREAM,0);
if(server == -1) {
localerror = errno;
fprintf(stderr, "Error: %s\n",strerror(localerror));
return 1;
}

port = atoi(argv[2]);

bzero(&server_addr,sizeof(server_addr));
server_addr.sin_family = AF_INET;	
status = inet_pton(AF_INET,argv[1],&server_addr.sin_addr.s_addr);
server_addr.sin_port = htons(port);

status = connect(server,(struct sockaddr *)&server_addr,sizeof(server_addr));
if(status != 0) {
localerror = errno;
printf("Error al conectarnos (%s)\n",strerror(localerror));
return 1;
}

time_t real;
struct tm *actual; //aveces necesitas declararlo así -> struct tm *actual;
time(&real);

actual= localtime(&real );

printf ("La hora actual de ahorita en este ratito: %2d:%02d:%02d\n", (actual->tm_hour)%12, actual->tm_min, actual->tm_sec);
printf ("La fechita actual de ahorita en este ratito de este dia: %2d:%02d:%02d\n", actual->tm_mday, actual->tm_mon+1, (actual->tm_year+1900));
// (actual->tm_hour)%24 si es 24h
//system("");
// printf("Ya me conecte!!!!\n");

cadena = (char *) calloc(1,10);

status = write(server,"Hola\n",5);
status = read(server,cadena,10);
printf("Nos regreso %s\n",cadena);
status = write(server,"Adios\r\n",7);
free(cadena);
close(server);
}

    Status
    API
    Training
    Shop
    Blog
    About

    © 2014 GitHub, Inc.
    Terms
    Privacy
    Security
    Contact

