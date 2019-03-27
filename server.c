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

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc,char *argv[])
{
   DIR *dir;
   struct dirent *ent;
   int key = 5;
   if(argc < 1)
   {
     printf("Not Valid \n");
     exit(1);
   }
   int sockfd, newsockfd, portno = 9999,n,i;
   char message[10],code[20],ch,dirPath[50],fileName[100];
   struct sockaddr_in server_addr, client_addr;//internet address
   socklen_t clientlen;

   sockfd = socket(AF_INET, SOCK_STREAM, 0); //af_inet is ipv4 and sock_stream is TCP
   if (sockfd < 0)
   {
     error("Error opening socket \n");
   }
   //bzero function is for clearing a buffer
   bzero((char *) &server_addr, sizeof(server_addr)); //clear the server_addr
   server_addr.sin_family=AF_INET;
	 server_addr.sin_addr.s_addr=INADDR_ANY;
	 server_addr.sin_port=htons(portno); //host to network short

   if(bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0) // binding socket and address
       error("Binding Failed. \n");

   listen(sockfd, 5);// here we are specifying that 5 client can connect

   clientlen = sizeof(client_addr);

   newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clientlen);//accepting client request
   if(newsockfd < 0)
   {
     error("Error on accept \n");
   }

  if ((dir = opendir ("/home/murali/Desktop/data")) != NULL)
  {
   /* print all the files and directories within directory */
  while ((ent = readdir (dir)) != NULL)
  {
    //code[0]='\0';
    //bzero(code,50);
    strcat(fileName,ent->d_name); // copying files name ito code buffer
    strcat(fileName," ");
    }
   closedir (dir);
   } else {
  /* could not open directory */
   error ("could not open directory \n");
   return EXIT_FAILURE;
   }
   n = write(newsockfd, fileName, strlen(fileName)); // write it in the network
   if (n < 0)
   {// checking for errors
     error("Error while writing in server(writing filename)\n");
   }
   code[0]='\0';
   //bzero(code,50);
   // Asking user to enter the file name
   // strcpy(code,"Enter file name:");
   // n = write(newsockfd, code, strlen(code)); // write it in the network
   // if (n < 0)
   // {// checking for errors
   //   error("Error while writing in server(Asking for file name)\n");
   // }
   code[0]='\0';
  // bzero(code,50);
   printf("Waiting for client's file name\n");
   n = read(newsockfd, code, 20);//readind file name
  // printf("murali \n");
   if (n < 0)
   {// checking for errors
     error("Error while Reading in server(reading file name from client)\n");
   }
  // sleep(10);
  // printf("murali dhar \n");
   printf("%s",code);
   dirPath[0]='\0';
   strcpy(dirPath,"/home/murali/Desktop/data/");
   strcat(dirPath,code);
   int sfd=open(dirPath,O_RDONLY|O_EXCL,0);
   //Encrypting and sending the files
   //sleep(6);
   while(read(sfd,message,sizeof(message))>0)
 	 {
    //printf("Inside while of parent");
    //printf("%s\n",message );
     //bzero(message,10);
 	  for(i = 0; i<10; ++i) //message[i] != '\0'
    {
 		  ch = message[i];

 		  if(ch >= 'a' && ch <= 'z')
      {
 			    ch = ch + key;

 			if(ch > 'z'){
 				ch = ch - 'z' + 'a' - 1;
 			}

 			message[i] = ch;
 		}
 		else if(ch >= 'A' && ch <= 'Z'){
 			ch = ch + key;

 			if(ch > 'Z'){
 				ch = ch - 'Z' + 'A' - 1;
 			}

 			message[i] = ch;
 		}
 	  }
    code[0]='\0';
    n = read(newsockfd, code, 20);//acknowledgement from client
    if (n < 0)
    {// checking for errors
      error("Error while waiting for acknowledgement inside while loop\n");
    }
    n = write(newsockfd, message, strlen(message)); // writing encrypted message in the network
    if (n < 0)
    {// checking for errors
        error("Error while writing into network (server side)\n");
    }

 	}

   code[0]='\0';
    n = read(newsockfd, code, 20);//acknowledgement from client
    if (n < 0)
    {// checking for errors
     error("Error while waiting for acknowledgement outside while loop\n");
    }
   code[0]='\0';
   //bzero(code,20);
   strcpy(code,"EOT");

   n = write(newsockfd, code, strlen(code)); // writing encrypted message in the network
   if (n < 0)
   {// checking for errors
      error("Error while writing into network (server side)\n");
   }
   printf("after sending file\n");
   close(newsockfd);
   close(sockfd);
   return 0;
}
