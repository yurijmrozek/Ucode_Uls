#include "uls.h"

static void sort(t_list *lf, t_cmd *c) {
    if (c->sort_type == sort_none)
        return;
    mx_sort_uls_list(lf, c, mx_strcmp_names);
    if (c->sort_type == sort_time) {
        if (c->time_type == time_mtime) {
            mx_sort_uls_list(lf, c, mx_strcmp_mtime);
        }
        else if (c->time_type == time_atime) {
            mx_sort_uls_list(lf, c, mx_strcmp_atime);
        }
        else if (c->time_type == time_ctime) {
            mx_sort_uls_list(lf, c, mx_strcmp_ctime);
        }
    }
    else if (c->sort_type == sort_size) {
        mx_sort_uls_list(lf, c, mx_strcmp_size);
    }
}

static void print_func(t_list *lf, t_cmd *c) {
    if (c->print_func == long_format)
        mx_print_long_format(lf, c);
    else if (c->print_func == std_format)
        mx_print_std_format(lf, c);
    else if (c->print_func == col_format)
        mx_print_col_format(lf, c);
    else if (c->print_func == m_format)
        mx_print_m_format(lf, c);
}

void mx_prepare_list_and_print(t_list *lf, t_cmd *c) {
    sort(lf, c);
    print_func(lf, c);
}
