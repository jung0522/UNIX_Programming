
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h>
#include <string.h>
int main(void)
{
	struct stat b; 
	char f[] = "a";
	stat(f, &b);
	printf("%s", f);
	printf("%d ", (int)b.st_ino); 
	printf("%d\n", (int)b.st_nlink);
	
	strcpy(f, "b"); 
	stat(f, &b);
	printf("%s", f);
	printf("%d ", (int)b.st_ino); 
	printf("%d\n", (int)b.st_nlink);
	
	strcpy(f, "c");
	lstat(f, &b);
	printf("%s", f);
	printf("%d", (int)b.st_ino);
	printf("%d\n", (int)b.st_nlink);
	return 0;
}
