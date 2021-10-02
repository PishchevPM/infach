all: fread fwrite

fread: fifo_read.c
	gcc -Wall -o fifo_read fifo_read.c

fwrite: fifo_write.c
	gcc -Wall -o fifo_write fifo_write.c

clean:
	rm -f *.o foo.fifo
