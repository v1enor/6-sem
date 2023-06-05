#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>
#include <stdbool.h>



int main(int argc, char *argv[])
{
	char *locale = setlocale(LC_ALL, "");
	int in;
	long pos, offs;               
	char buffer[10];
	
	in = open("./OS09_05.txt",O_RDONLY);
	offs = 0L;
	pos = lseek(in, offs, SEEK_SET);
	printf("Current position (SEEK_SET, offset = 0L) = %ld\n", pos);
	
	offs = 10L;
	read(in, buffer, 10);
	printf("10 chars read: %s\n", buffer);
	pos = lseek(in, offs, SEEK_CUR);
	printf("Current position (SEEK_CUR, offset = 10L) = %ld\n", pos);
	
	offs = 20L;
	pos = lseek(in, offs, SEEK_END);
	printf("Current position (SEEK_END, offset = 20L) = %ld\n", pos);
	close(in);
	return 0;
}
