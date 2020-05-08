#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

char gusti[100][100];
char gusti2[100][100];
int line=0, i=0, chare=0;

struct test {
	char name[100][100];
};

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

void remdup(int n){
  int j,k;
	for(i=0; i<n; i++)
	{
		for(j=i+1; j<n; j++)
		{
			if(strcmp(gusti[i],gusti[j])==0 && strcmp(gusti2[i],gusti2[j])==0)
			{
				for(k=j; k<n; k++)
				{
					strcpy(gusti[k],gusti[k+1]);
          strcpy(gusti2[k],gusti2[k+1]);
				}
				n--;
				line--;
				j--;
			}
		}
	}
}

void NSort(int n)
{
  int i, j;
  char key[100];
  char key2[100];
  for (i = 0; i < n; i++)
  {
      strcpy(key,gusti[i]);
      strcpy(key2,gusti2[i]);
      j = i - 1;
      while (j >= 0 && atoi(gusti[j])>atoi(key))
      {
            strcpy(gusti[j+1],gusti[j]);
            strcpy(gusti2[j+1],gusti2[j]);
            j = j - 1;
      }
      strcpy(gusti[j+1],key);
      strcpy(gusti2[j+1],key2);
  }
}

char*
strcat(char *d,char *s)
{
	char *temp=d;
	while(*d) ++d;
	while(*s) *d++=*s++;
	*d=0;
	return temp;
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
			if(flag==0) {
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
	for(i=0; i < line+1; i++) {
		printf(1,"%s ",gusti[i]);
		printf(1,"%s\n",gusti2[i]);
	}
}

void Rprinter(){
	for(i=line; i >= 0; i--) {
		printf(1,"%s ",gusti[i]);
		printf(1,"%s\n",gusti2[i]);
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		Reader(argv[1]);
		insertionSort(line+1,0,argv[1]);
		printer();
		exit();
	}
	if(argc >= 3)
	{
		if(argv[1][0]=='-') {
			if(argv[1][1]=='r') {
				Reader(argv[2]);
				insertionSort(line+1,0,argv[2]);
				Rprinter();
				exit();
			}
			if(argv[1][1]=='c') {
				Reader(argv[2]);
				insertionSort(line+1,1,argv[2]);
				printf(1,"Sorted\n");
				exit();
			}
			if(argv[1][1]=='u') {
				Reader(argv[2]);
        insertionSort(line+1,0,argv[2]);
        remdup(line+1);
        printer();
				exit();
			}
      if(argv[1][1]=='M'){
        printf(2,"error : available in sort2\n");
        exit();
      }
      if(argv[1][1]=='n'){
        Reader(argv[2]);
        line++;
        insertionSort(line,0,argv[2]);
        NSort(line);
        line--;
        printer();
        exit();
      }
			if(argv[1][1]=='k' && argv[1][2]=='2') {
				Reader(argv[2]);
				insertionSort(line+1,0,argv[1]);
				printer();
				exit();
			}
			if(argv[1][1]=='o') {
				Reader(argv[2]);
				insertionSort(line+1,0,argv[1]);
				// outputter();
				int fd;
				struct test t;
				for(i=0; i < line+1; i++) {
					strcpy(t.name[i],gusti[i]);
					strcat(t.name[i]," ");
					strcat(t.name[i],gusti2[i]);
					int k=strlen(t.name[i]);
					t.name[i][k+1]='\n';
				}
				fd = open(argv[3], O_CREATE | O_RDWR);
				int size=sizeof(t);
				if(write(fd, &t, size) != size) {
					printf(1, "error: write to %s file failed\n",argv[3]);
					exit();
				}
				exit();
			}
		}
		exit();
	}

}
