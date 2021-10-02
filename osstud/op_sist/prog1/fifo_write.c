#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define FIFO_FNAME "fff.fifo"

int main(int argc, char *argv[]){

	int fd;
	size_t size;

	/* otkrivaem fifo na zapis.*/
	if((fd = open(FIFO_FNAME, O_WRONLY)) < 0) {
	/* otkrit ne udalos */
		printf("Can't open FIFO for reading\n");
		exit(-1);
	}

	size = write(fd, "Hello, world!", 14);

	if(size != 14) {
	/* zapisat 14 ne udalos */
		printf("Can't write all string to FIFO\n");
        }

        close(fd);

	return 0;
}
