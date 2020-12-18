#include "uls.h"

void mx_print_nlink(t_file *file, t_maxlens_for_print *ml){
    char *tmp;

    tmp = mx_itoa(file->ffs.st_nlink);
    mx_printspaces(1 + ml->l_links - mx_strlen(tmp));
    free(tmp);
    mx_printint(file->ffs.st_nlink);
}
