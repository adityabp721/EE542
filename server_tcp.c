/* Enhanced simple server with the fix to the zombie problem in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
void SigCatcher(int n)
{
    wait3(NULL, WNOHANG, NULL);
}
void dostuff(int sock)
{
    int n;
    char buffer[256];
    bzero(buffer, 256);
    n = read(sock, buffer, 255);
    if (n < 0)
        error("ERROR reading from socket");
    printf("Here is the message: %s\n", buffer);
    n = write(sock, "I got your message", 18);
    if (n < 0)
        error("ERROR writing to socket");
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        pid_t pid = fork();
        signal(SIGCHLD, SigCatcher);
        if (pid < 0)
        {
            error("ERROR on fork");
        }
        if (pid == 0)
        {
            close(sockfd);
            dostuff(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
    return 0;
}
