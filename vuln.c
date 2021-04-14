
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// gcc -m32 vuln.c  -o vuln-format -z execstack -fno-stack-protector
// echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
//  env - /home/renault/remote_buffer_overflow_app/vuln 5602
// to avoid overlay  env - /home/renault/remote_buffer_overflow_app/vuln 5602
void error(char *msg)
{
perror(msg);
exit(1);
}
void viewer(char *string)
{
//declaration of a char buffer
//char buffer[1024];
char buffer[512];
//we copy the parameter string to that buffer
strcpy(buffer,string);
//finally we print the content of the string buffer to stdout
printf("size :\n%d\n", strlen(buffer) ); // prints 10
printf("The user entered: %s",buffer);

}
int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno, clilen;
char buffer[2000];
struct sockaddr_in serv_addr, cli_addr;
 int n;

 if (argc < 2) {
 fprintf(stderr,"ERROR, no port provided\n");
 exit(1);
 }
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
 if (sockfd < 0)
 error("ERROR opening socket");
 bzero((char *) &serv_addr, sizeof(serv_addr));
 portno = atoi(argv[1]);
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port = htons(portno);
 if (bind(sockfd, (struct sockaddr *) &serv_addr,
 sizeof(serv_addr)) < 0)
 error("ERROR on binding");
 listen(sockfd,5);
 clilen = sizeof(cli_addr);
 while(1)
 {
 newsockfd = accept(sockfd,
 (struct sockaddr *) &cli_addr,
 &clilen);
 if (newsockfd < 0)
 error("ERROR on accept");

 bzero(buffer,256);
 n = read(newsockfd,buffer,2000); // read 2000  bytes 
 if (n < 0) error("ERROR reading from socket");
 printf("buffer :%p",buffer);
 printf("buffer_addr :%p",&buffer);
 viewer(buffer);
 //n = write(newsockfd,"The message is been printed to server stdout", strlen("The message is been printed to server's stdout"));
 if (n < 0) error("ERROR writing to socket");
 }
 return 0;
} 