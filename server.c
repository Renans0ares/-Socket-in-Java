#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include <sys/un.h>
#include <signal.h>
#include <sys/socket.h>


int gestisci(int connection_fd){
    int nbytes;
    char buffer[256];
    

    nbytes = read(connection_fd, buffer, 256);
    buffer[nbytes] = 0;
    printf("MENSAGEM DO CLIENTE!: %s\n", buffer);
    nbytes = sprintf(buffer, "Olá você do servidor\a\n");
    
    write(connection_fd, buffer, nbytes);
    close(connection_fd);
    return 0;
}

int main(void){ 

    struct sockaddr_un serverAddress;
    struct sockaddr* serverSockAddrPtr;
    int socket_fd, conn_fd, serverAddressLength;

    pid_t child;

    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

    if(socket_fd < 0){
        printf("Falha na criação do socket\a\n");
        return 1;} unlik("demo_socket");

        serverAddress.sun_family = AF_LOCAL;
        sprintf(serverAddress.sun_path, "demo_socket");

        serverSockAddrPtr = (struct sockaddr*) &serverAddress;
        serverAddressLength = sizeof(serverAddress);
        if(bind(socket_fd, serverSockAddrPtr, serverAddressLength) != 0){
            printf("O socket Falhou\a\n");
            return 1;
        }
        if(listen(socket_fd, 5) != 0){
            printf("Houve uma falha no socket");
            return 1;
        }

        while((conn_fd = accept(socket_fd, NULL, NULL))>-1){
            printf("Server: Nova Conexão! [%d]\n", conn_fd);
            child=fork();
            if(child == 0){
                return (gestisci(conn_fd));
            }
            close(conn_fd);
        }
        close(socket_fd);
        unlink("demo_socket");
        return 0;    

}
