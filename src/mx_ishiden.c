#include "uls.h"

bool mx_ishidden(char *filename, t_list *q) {
    if (filename && !q)
        return ((filename[0] == '.') ? true : false);
    else if (!filename && q)
        return (((t_file *)q->data)->filename[0] == '.' ? true : false);
    else
        return false;
}

