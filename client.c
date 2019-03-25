#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netdb.h>
void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc,char *argv[])
{
  int sockfd, portno = 9999,n,i;
  char message[10],code[20],ch;
  struct sockaddr_in server_addr;
  struct hostent *server; // used to store information about given host
  if(argc < 2)
  {
    printf("Not Valid \n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0); //af_inet is ipv4 and sock_stream is TCP
  if (sockfd < 0)
  {
    error("Error opening socket \n");
  }
  server = gethostbyname(argv[1]); // get ip address
  if(server == NULL)
  {
    fprintf(stderr,"Error no such host");
  }
  bzero((char *) &server_addr, sizeof(server_addr)); //clear the server_addr
  server_addr.sin_family=AF_INET;
  bcopy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr,server->h_length);
  server_addr.sin_port=htons(portno); // host to network ahort
  if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
			error("Connection failed");
  while(1)
  {
    // reading all the files available
    bzero(code,20);
    n = read(sockfd, code, 20);
    if (n < 0)
    {// checking for errors
      error("Error while Reading\n");
    }
    printf("From Server :%s\n",code);
    if(strcmp(code,"Enter file name:")) // when we get this message, we break from while for writing purpose
      break;
  }
  bzero(code,20);
  gets(code);// getting client input
  n = write(sockfd, code, strlen(code)); // writing the file name which is suppose to be sent
  if (n < 0)
  {// checking for errors
      error("Error while writing \n");
  }
}
