#ifndef IOCTL_H
#define IOCTL_H

#include <linux/ioctl.h>

typedef struct {
	int i;
	int j;
} ioctl_struct;

#define CALC_IOCTL_MAGIC    0x33

#define CALC_IOCTL_ADD      _IO(CALC_IOCTL_MAGIC, 1)
#define CALC_IOCTL_SUB      _IO(CALC_IOCTL_MAGIC, 2)
#define CALC_IOCTL_MUL      _IO(CALC_IOCTL_MAGIC, 3)
#define CALC_IOCTL_DIV      _IO(CALC_IOCTL_MAGIC, 4)
#define CALC_IOCTL_CLS      _IO(CALC_IOCTL_MAGIC, 5)

#define CALC_IOCTL_DATA01   _IOW(CALC_IOCTL_MAGIC, 11, int)
#define CALC_IOCTL_DATA02   _IOW(CALC_IOCTL_MAGIC, 12, int)

#define CALC_IOCTL_RESULT   _IOR(CALC_IOCTL_MAGIC, 21, int)

#endif