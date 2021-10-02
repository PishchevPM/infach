#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define FIFO_FNAME "fff.fifo"
#define BUF_LEN 14

int main(int argc, char *argv[])
{
	int fd;
	size_t size;
	char buf[BUF_LEN];

	/* obnulaem masku */
	(void)umask(0);

	/* sozdaem FIFO s imenem fff.fifo */
	if(mknod(FIFO_FNAME, S_IFIFO | 0666, 0) < 0){
	/* sozdat ne udalos */
		printf("Can't create FIFO\n");
		exit(-1);
	}

        /* mi nahodimsa v processe, kotorii budet 4itat inf ot pishuschego processa*/
	if((fd = open(FIFO_FNAME, O_RDONLY)) < 0){
	/* otkrit ne udalos */
		printf("Can't open FIFO for reading\n");
		exit(-1);
        }

	/* poprubuem pro4itat 14 bait */
	size = read(fd, buf, BUF_LEN);
        if(size < 0){
	/* pro4itat ne smogli */
		printf("Can't read string\n");
		exit(-1);
        }

	printf ("Readed %d bytes\n", size);

	printf("%s\n", buf);

	close(fd);

	return 0;
}
