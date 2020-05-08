#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

char gusti[100][100];
char gusti2[100][100];
int line=0, i=0, chare=0;

int kkk(char satu[100]){
    if(strcmp(satu,"january")==0) return 1;
    else if(strcmp(satu,"february")==0) return 2;
    else if(strcmp(satu,"march")==0) return 3;
    else if(strcmp(satu,"april")==0) return 4;
    else if(strcmp(satu,"may")==0) return 5;
    else if(strcmp(satu,"june")==0) return 6;
    else if(strcmp(satu,"july")==0) return 7;
    else if(strcmp(satu,"august")==0) return 8;
    else if(strcmp(satu,"september")==0) return 9;
    else if(strcmp(satu,"november")==0) return 10;
    else if(strcmp(satu,"october")==0) return 11;
    else if(strcmp(satu,"december")==0) return 12;
    else return 0;
}

void MonthSort(int n)
{
  int i, j;
  char key[100];
  char key2[100];
  for (i = 0; i < n; i++)
  {
      strcpy(key,gusti[i]);
      strcpy(key2,gusti2[i]);
      j = i - 1;
      while (j >= 0 && kkk(gusti[j])>kkk(key))
      {
            strcpy(gusti[j+1],gusti[j]);
            strcpy(gusti2[j+1],gusti2[j]);
            j = j - 1;
      }
      strcpy(gusti[j+1],key);
      strcpy(gusti2[j+1],key2);
  }
  gusti[line+1][0]='\0';
  gusti2[line+1][0]='\0';
}

void insertionSort(int n,int check,char* argv)
{
	int i, j;
	char key[100];
	char key2[100];
	for (i = 0; i < n; i++)
	{
		strcpy(key,gusti[i]);
		strcpy(key2,gusti2[i]);
		j = i - 1;
		while (j >= 0 && strcmp(gusti[j],key)>0)
		{
			if(check==1) {
				printf(1,"sort: %s:%d: disorder: %s\n",argv,i+1,key);
				exit();
			}
			else{
				strcpy(gusti[j+1],gusti[j]);
				strcpy(gusti2[j+1],gusti2[j]);
				j = j - 1;
			}
		}
		strcpy(gusti[j+1],key);
		strcpy(gusti2[j+1],key2);
	}
}


void Reader(char *argv){
  int file1 = open(argv, 0);
  struct stat st1;
  if (file1 < 0)
  {
    printf(2,"Error : File %s cannot open", argv);
    exit();
  }
  if (fstat(file1, &st1) < 0)
  {
    printf(2, "Error : cannot stat %s\n", argv);
    close(file1);
    exit();
  }
  if (st1.type != T_FILE)
  {
    printf(2, "sort : %s is not a file\n", argv);
    close(file1);
    exit();
  }
  char buf1[10000];
  int sz1 = read(file1, buf1, sizeof(buf1));
  buf1[sz1] = '\0';
  int col = 0;
  int idx1 = 0;
  int flag = 0;
  while (idx1 < sz1-1)
  {
    if (buf1[idx1] == ' ')
    {
      gusti[line][col]='\0';
      flag++;
      col = 0;
    }
    else if (buf1[idx1] == '\n')
    {
      gusti2[line][col]='\0';
      line++;
      col = 0;
      flag = 0;
    }
    else
    {
      if(flag==0){
        gusti[line][col]=buf1[idx1];
      }
      else{
        gusti2[line][col]=buf1[idx1];
      }
      col++;
      chare++;
    }
    idx1++;
  }
  gusti[line][col]='\0';
  gusti[line+1][0]='\0';
  gusti2[line][col]='\0';
  gusti2[line+1][0]='\0';
}

void printer(){
  for(i=0; i < line+1;i++){
    printf(1,"%s ",gusti[i]);
    printf(1,"%s\n",gusti2[i]);
  }
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
    printf(2,"error : available in sort\n");
    exit();
	}
	if(argc >= 3)
  {
    if(argv[1][0]=='-'){
      if(argv[1][1]=='r'){
        printf(2,"error : available in sort\n");
        exit();
      }
      if(argv[1][1]=='c'){
        printf(2,"error : available in sort\n");
        exit();
      }
      if(argv[1][1]=='M'){
        Reader(argv[2]);
        line++;
        insertionSort(line,0,argv[1]);
        MonthSort(line);
        line--;
        printer();
        exit();
      }
      if(argv[1][1]=='u') {
        printf(2,"error : available in sort\n");
        exit();
			}
      if(argv[1][1]=='n'){
        printf(2,"error : available in sort\n");
        exit();
      }
      if(argv[1][1]=='k' && argv[1][2]=='2'){
        printf(2,"error : available in sort\n");
        exit();
      }
      if(argv[1][1]=='o'){
        printf(2,"error : available in sort\n");
        exit();
      }
    }
    exit();
	}

}
