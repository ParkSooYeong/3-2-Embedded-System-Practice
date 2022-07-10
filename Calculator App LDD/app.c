#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#include "ioctl.h"

int main()
{
	int num;
	int fd;
	int32_t value, number1, number2, output, operation;

	printf("\nStart Application\nOpening Driver ...\n");

	fd = open("/dev/calc_device", O_RDWR);
	if(fd<0) {
		printf("Cannot open device file ...\n");
		return 0;
	}

	printf("Clear Kernel Data ...\n");
	ioctl(fd, CALC_IOCTL_CLS);

Start:
	printf("\n*************************************\n");
	printf("Start Calc in Linux Kernel !!\n\n");
	printf("\t* Enter 1st value : ");
	scanf("%d", &number1);
	getchar();

	printf("\t* Enter 2nd value : ");
	scanf("%d", &number2);
	getchar();

	printf("\nWriting value to driver ...\n\n");

	ioctl(fd, CALC_IOCTL_DATA01, (int32_t*) &number1);
	ioctl(fd, CALC_IOCTL_DATA02, (int32_t*) &number2);

Operation:
	printf("Operation to perform\n\n");
	printf("\t1. Add\n\t2. Subtract\n\t3. Multiply\n\t4. Exit\n\n\tSelect : ");

/*
	printf("\
		\t1. Add\n \
		\t2. Subtract\n \
		\t3. Multiply\n \
		\t4. Exit\n\n \
		\tSelect : ");
*/

	scanf("%d", &num);
	if(num > 4 && num < 1) {
		printf("Invalid Selection ...\nTry Again ...\n");
		goto Operation;
	}

	if(num == 1) ioctl(fd, CALC_IOCTL_ADD);
	else if(num == 2) ioctl(fd, CALC_IOCTL_SUB);
	else if(num == 3) ioctl(fd, CALC_IOCTL_MUL);
	else if(num == 4) {
		printf("\nClosing driver !!\n\n");
		close(fd);
		return 0;
	}

	printf("\n* Get Result from Kernel ...\n");
	ioctl(fd, CALC_IOCTL_RESULT, (int32_t*)&value);
	printf("! Return value from Kernel = %d\n", value);
	goto Start;
}
