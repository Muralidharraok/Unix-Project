#include <stdio.h>
#include <string.h>

int main()
{
  char a[30];
  char b[20]="mm.txt";
  a[0]='\0';
  printf("%s\n",a);
  //printf("%c\n",a[0/]);
  //printf("%c\n",a[2]);
  //printf("%c\n",a[4]);
//  bzero(a,3);

  //memset(a,0,sizeof(a));
  //printf("%s\n",a);
  //a[0]='\0';
  strcat(a,"/home/Desktop/");
  strcat(a,b);
  printf("%s\n",a);
}
