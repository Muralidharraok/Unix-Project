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
  int sockfd, portno = 9999,n,i,key;
  char message[10],code[20],ch,fileName[100];
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
    error("Error opening socket in client \n");
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
			error("Connection failed in client");
  printf("From Server :");
    // reading all the files available
  code[0]='\0';
    //bzero(code,20);
  n = read(sockfd, fileName, 100);
  if (n < 0)
  {// checking for errors
    error("Error while Reading files names in client\n");
  }
  printf("%s\n",fileName);
  code[0]='\0';
  //bzero(code,20);
  printf("Enter the file name:\n");
  scanf("%s",code);// getting client input
  n = write(sockfd, code, strlen(code)); // writing the file name which is suppose to be sent
  if (n < 0)
  {// checking for errors
      error("Error while writing file name in client\n");
  }
  code[0]='\0';
  //bzero(code,20);
  printf("Enter the distination file name \n");//Name of pdestination file
  scanf("%s",code);
  printf("Enter the key \n");//Asking key for decryption
  scanf("%d",&key);
  int dfd=open(code,O_WRONLY|O_CREAT,S_IRWXU|S_IRGRP|S_IWGRP|S_IROTH);
  printf("after opening distination file \n");
  code[0]='\0';
  strcpy(code,"ack");
  while(1)
  {
    //printf("Inside while of child\n");
    message[0]='\0';
    //bzero(message,10);

    n = write(sockfd, code, strlen(code)); // sending the acknowledgement
    if (n < 0)
    {// checking for errors
        error("Error while sending acknowledgement to server\n");
    }

    n = read(sockfd, message, 10);
    if (n < 0)
    {// checking for errors
      error("Error while Reading input of the file in client\n");
    }
    if (strcmp(message,"EOT") == 0)
    {
      break;
    }
    for(i = 0; i<10; ++i) //message[i] != '\0'
    {
      ch = message[i];
      if(ch >= 'a' && ch <= 'z')
        {
         ch = ch - key;

         if(ch < 'a')
         {
           ch = ch + 'z' - 'a' + 1;
         }
         message[i] = ch;
        }
      else if(ch >= 'A' && ch <= 'Z')
      {
        ch = ch - key;
        if(ch < 'A')
        {
          ch = ch + 'Z' - 'A' + 1;
        }
        message[i] = ch;
      }
      }
     write(dfd,message,sizeof(message));
  }
 return 0;

}
