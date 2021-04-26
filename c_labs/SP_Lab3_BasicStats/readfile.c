#include <stdio.h>
#include <stdlib.h>
#ifndef READFILE_C_INCLUDED
#define READFILE_C_INCLUDED

static FILE *fp;

int open_file(const char *file) {

    fp = fopen(file, "a+");
    if (!fp) {
        return -1;
    }
    return 0;
}

int close_file() {
    return fclose(fp);
}

int read_int(int *dest) {
    int ret;
    ret = fscanf(fp, "%d", dest);
    if (ret == -1) return -1;
    return 0;
}

int read_string(char s[]) {
    int ret;
    ret = fscanf(fp, "%s", s);
    if (ret == -1) return -1;
    return 0;
}

int read_float(float *dest) {
    int ret;
    ret = fscanf(fp, "%f", dest);
    if (ret == -1) return -1;
    return 0;
}

#endif // READFILE_C_INCLUDED
