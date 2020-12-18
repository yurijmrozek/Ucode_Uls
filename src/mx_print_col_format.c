#include "uls.h"

void mx_print_col_format(t_list *lf, t_cmd *c) {
    t_file *tmp;

    for (t_list *q = lf; q; q = q->next) {
        tmp = q->data;
        if (c->format_g)
            mx_print_color_name(tmp);
        else
            mx_printstr(tmp->filename);
        if (q->next == NULL)
            break;
        mx_printchar('\n');
    }
    mx_printchar('\n');
}
