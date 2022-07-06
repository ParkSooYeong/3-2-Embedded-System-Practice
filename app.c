#include <stdio.h>
#include <string.h>		// strlen()
#include <unistd.h>		// read, write
#include <fcntl.h>		// open, close, O_RDWR, O_NONBLOCK

#define BUFF_SIZE 1024

int main()
{
	int	fd;
	char *str_hello	= "Hello, Loopback Buffer !!";
	char  buf[BUFF_SIZE];

	if(0 < (fd = open("/dev/loopback", O_RDWR))) {
		write(fd, str_hello, strlen(str_hello)+1); // +1: include NULL
		read( fd, buf, BUFF_SIZE);
		printf("%s\n", buf);
		close(fd);
	}

	return 0;
}
