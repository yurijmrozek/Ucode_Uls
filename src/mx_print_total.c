#include "uls.h"

void mx_print_total(t_list *lf) {
    blkcnt_t res = 0;
    t_file *tmp;

    for (t_list *q = lf; q != NULL; q = q->next) {
        tmp = q->data;
        res += tmp->ffs.st_blocks;
    }
    mx_printstr("total ");
    mx_printint((int)res);
    mx_printstr("\n");
}
