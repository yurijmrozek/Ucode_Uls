#include "uls.h"

bool mx_strcmp_size(void *d1, void *d2, t_cmd *c) {
    off_t s1 = ((t_file *)d1)->ffs.st_size;
    off_t s2 = ((t_file *)d2)->ffs.st_size;

    if (s1 < s2 && !(c->print_reverse))
        return true;
    else if (s1 > s2 && c->print_reverse)
        return true;
    else
        return false;
}
