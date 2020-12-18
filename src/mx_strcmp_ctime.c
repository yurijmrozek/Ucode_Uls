#include "uls.h"

bool mx_strcmp_ctime(void *d1, void *d2, t_cmd *c) {
    time_t s1;
    time_t s2;

    s1 = ((t_file *)d1)->ffs.st_ctime;
    s2 = ((t_file *)d2)->ffs.st_ctime;
    if (s1 < s2 && !(c->print_reverse))
        return true;
    else if (s1 > s2 && c->print_reverse)
        return true;
    else
        return false;
}
