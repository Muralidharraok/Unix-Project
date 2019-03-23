#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int len,i,key_count=0,Variable_key;
char message[1],ch;
char *p;
char encrypt(int key,char *message)
{
for(i=0; *message!='\0';i++)
{
  *message=*message+key;
   message++;
}
  /*for(i = 0; *message[i] != '\0'; ++i)
  {
     ch = message[i];
     ch = ch + Variable_key;
     printf("%c\n",ch);
     //ch = ch - Variable_key;
     message[i] = ch;
  }*/
  //return(message);
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
    key_in_ASCII[i] = ((int)key[i])%26;
  }
  int sfd=open(argv[3],O_RDONLY|O_EXCL,0);
	int dfd=open(argv[4],O_WRONLY|O_CREAT,S_IRWXU|S_IRGRP|S_IWGRP|S_IROTH);
  if (strcmp( argv[1], "-e" ) == 0 )
  {
    while(read(sfd,message,sizeof(message))>0)
	  {
      p=&message[0];
      Variable_key = key_in_ASCII[key_count];
      encrypt(Variable_key,p);
      write(dfd,message,sizeof(message));
      key_count=(key_count+1)%len;
    }
  }
}
