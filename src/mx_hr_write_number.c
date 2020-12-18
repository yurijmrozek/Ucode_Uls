#include "uls.h"

void mx_hr_write_number(char *size, off_t st_size) {
    int c;
    off_t num = st_size;

    for (c = 3; c > 0; c--) {
        if (num > 0) {
            size [c - 1] = num % 10 + 48;
            num /= 10;
        }
        else
            size[c - 1] = ' ';
    }
}

