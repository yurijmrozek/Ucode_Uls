#include "uls.h"

int mx_hr_get_pow(off_t st_size) {
    off_t num = st_size;
    int pow = 0;

    while (num >= 1000) {
        num /= 1024;
        pow += 10;
    }
    return pow;
}

