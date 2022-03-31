#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"gameplay.h"
int main(int argv,char*args[]){
  int fd,i,j;
  truc tmp;
  couple tab[20][40];
  off_t fsize,ctrl;
  if(argv!=2){
    fprintf(stderr,"%s map/<nomde de fichier>\n",args[0]);
    exit(EXIT_FAILURE);
  }
  if((fd=open(args[1],O_RDONLY))==-1){
    perror("open()\n");
    exit(EXIT_FAILURE);
  }
  if((fsize=lseek(fd,0,SEEK_END))==-1){
    perror("lseek()\n");
    exit(EXIT_FAILURE);
  }
  if(lseek(fd,0,SEEK_SET)==-1){
    perror("lseek\n");
    exit(EXIT_FAILURE);
  }
  if(read(fd,tab,sizeof(couple)*20*40)==-1){
    perror("read()\n");
    exit(EXIT_FAILURE);
  }
  for(i=0;i<20;i++){
    for(j=0;j<40;j++){
      printf("[%d,%c]",tab[i][j].color,tab[i][j].c);
    }
    printf("\n");
  }
  while((ctrl=lseek(fd,0,SEEK_CUR))!=fsize){
    if(ctrl==-1){
      perror("lseek()\n");
      exit(EXIT_FAILURE);
    }
    if(read(fd,&tmp.diff,sizeof(unsigned short)+sizeof(unsigned char)+sizeof(caracteristique))==-1){
      perror("read()\n");
      exit(EXIT_FAILURE);
    }
    if(read(fd,tmp.nom,tmp.size)==-1){
      perror("read()\n");
      exit(EXIT_FAILURE);
    }
    printf("%s %hd %d[%d,%d,%d,%d,%d]\n",tmp.nom,tmp.diff,tmp.size,tmp.attr.pv,tmp.attr.armure,tmp.attr.force,tmp.attr.vitesseDeplacement,tmp.attr.vitesseFrappe);
  }
  if(close(fd)==-1){
    perror("close()\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
