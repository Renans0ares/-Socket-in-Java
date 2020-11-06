// Está com os problemas na parte da biblioteca ainda Orlando. Como mudamos de liguagem ficou um pouco mais corrido entao estamos postando essa para realizar alterações 
//posteriormente

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
# include <sys/socket.h>
#include <pthread.h>
#include <sys/un.h>
#include <signal.h>

int main(void){
    struct sockaddr_un serverAdress;
    struct sockadder serverScokAddrPtr;

    int socket_fd, nbytes, serverAdressLength;
    char buffer[256];
    socket_fd = socket(PF_LOCAL,SOCK_STREAM, 0);
    if(socket_fd < 0){
        printf("Erro ao criar cliente\a\n");
        return 1;
    }
    serverAdress.sun_family= AF_LOCAL;
    sprintf(serverAdress.sun_path,"demo_socket");

    serverScokAddrPtr = (struct sockaddr*) &serverAdress;
    serverAdressLength = sizeof(serverAdress);

    if(connect(socket_fd, serverScokAddrPtr, serverAdressLength)){
        printf("Conexão do cliente falhou\a\n");
        return 1;
    }
    printf("(Cliente) Escreva uma mensagem aqui:");
    fgets(buffer, 255, stdin);
    write(socket_fd, buffer, strlen(buffer));
    nbytes = read(socket_fd, buffer, 256);
    buffer[nbytes] = '\0';
    printf("Resposta do servidor : [%s]\n", buffer);
    return 0;
}
