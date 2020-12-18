#include "uls.h"

bool mx_strcmp_f_d_bool(void *d1, void *d2) {
    char *s1 = d1;
    char *s2 = d2;

    while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0') {
        s1++;
        s2++;
    }
    if ((*s1 - *s2) > 0)
        return true;
    else
        return false;
}
