#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<dirent.h>


int main()
{
  DIR *dir;
  struct dirent *ent;
  char code[10];
if ((dir = opendir ("/home/murali/Desktop/data")) != NULL) {
 /* print all the files and directories within directory */
while ((ent = readdir (dir)) != NULL) {
  //char code[10]= (ent->d_name);
  //n = write(newsockfd, );
  strcpy(code,ent->d_name);
  printf ("%s\n", code);
 }
 closedir (dir);
 } else {
/* could not open directory */
 perror ("could not open directory");
 return EXIT_FAILURE;
 }
}


/*
int len,i,key_count=0,dfd;
int fd1[2];
int fd2[2];
int Variable_key;
char message[10],ch;
char *p;
pid_t pid;

char encrypt(int key)
{


  pid = fork();
  //char *keyinS = (char)key;
  //char *FdinS = (char)dfd;

  if(pid < 0)
  {
    perror("Fork error\n");
    exit(1);
  }
  if(pid == 0)
  {
    printf("child\n");

    //char *array[]={"./child","encrypt",NULL};

    if(execl("/home/murali/Desktop/UNIXProject/child","./child","array",(char *)0)<0)
    {
      perror("Execv error\n");
    }
    exit(0);
  }
  //sleep(2);
  //printf("Parent\n");
  //close(fd1[0]);
  //write(fd1[1], message, strlen(message)+1);
  //close(fd1[1]);
  //wait(NULL);
  //close(fd2[1]);
  //read(fd2[0], message, 100);
  //close(fd2[0]);
  //sleep(5);
  //printf("hello\n");
  //execlp("./");
  /*for(i=0; i<len;i++)
  {
    *message=(*message+key) % 127;
     message++;
  }
}
char decrypt(int key,char *message)
{
  for(i=0; i<len;i++)
  {
    int tempValue =0;
    tempValue = *message-key;
    if (tempValue < 0)
    {
      tempValue+=127;
    }
    *message=(tempValue) % 127;
     message++;
  }
}
int main(int argc, char *argv[])
{
  if(argc != 5)
  {
    printf("Arguements should be only 5: \n command -option key source destination \n");
    exit(0);
  }

  len=strlen(argv[2]);
  char key[len];
  int key_in_ASCII[len];
  strcpy(key,argv[2]);

  for(i=0;i<len;i++)
  {
    key_in_ASCII[i] = (int)key[i];
  }

//  for(i = 0; i < len; i++) {
  //  printf("%d\n", key_in_ASCII[i]);
  //}
  int sfd=open(argv[3],O_RDONLY|O_EXCL,0);
      dfd=open(argv[4],O_WRONLY|O_CREAT,S_IRWXU|S_IRGRP|S_IWGRP|S_IROTH);
  if (strcmp( argv[1], "-e" ) == 0 )
  {
    //while(read(sfd,message,sizeof(message))>0)
    //{
      p=&message[0];
      Variable_key = 5;//key_in_ASCII[key_count];

      encrypt(Variable_key);
      write(dfd,message,sizeof(message));
      //key_count=(key_count+1)%len;
    //}
  }
  else if(strcmp( argv[1], "-d" ) == 0)
  {
    while(read(sfd,message,sizeof(message))>0)
    {
      p=&message[0];
      Variable_key = key_in_ASCII[key_count];
      decrypt(Variable_key,p);
      write(dfd,message,sizeof(message));
      key_count=(key_count+1)%len;
    }
  }
}
*/
