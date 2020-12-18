#include "uls.h"

void mx_clear_filesattr_list(t_list **fl, t_cmd *c) {
    t_list *q = *fl;
    t_list *tmp = NULL;

    if (!(*fl) || !fl)
        return;
    while (q) {
        mx_clear_filesattr(q->data, c);
        tmp = q->next;
        free(q);
        q = tmp;
    }
    *fl = NULL;
}
