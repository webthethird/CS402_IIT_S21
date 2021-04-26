#include <stdio.h>
#include <stdlib.h>
#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

int open_file(const char file[]);
int close_file(void);
int read_int(int *dest);
int read_string(char s[]);
int read_float(float *dest);

#endif // READFILE_H_INCLUDED
