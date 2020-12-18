#include "uls.h"

bool mx_strcmp_names(void *d1, void *d2, t_cmd *c) {
    char *s1 = ((t_file *)d1)->filename;
    char *s2 = ((t_file *)d2)->filename;

    while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0') {
        s1++;
        s2++;
    }
    if ((*s1 - *s2) > 0 && !(c->print_reverse))
        return true;
    else if ((*s1 - *s2) < 0 && c->print_reverse)
        return true;
    else
        return false;
}
