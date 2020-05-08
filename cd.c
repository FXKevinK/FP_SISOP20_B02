#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int file1 = open(argv[1], 0);
  struct stat st1;
	if (argc < 2)
	{
	printf(2,"cd : too few arguments\n");
    exit();
  }else if(argc > 2){
    printf(2,"cd : too many arguments\n");
		exit();
	}
  fstat(file1, &st1);
  if (st1.type == T_FILE)
  {
    printf(2, "cd : %s is not a directory\n", argv[1]);
    close(file1);
    exit();
  }else{
    if (chdir(argv[1]) < 0)
  	{
  		printf(1, "cd : cannot open directory\n");
  	}
  }
	exit();
}
