#include "uls.h"

static void print_ow_gr(t_file *file, t_maxlens_for_print *ml, t_cmd *c) {
    if (c->print_owner) {
        mx_printstr(file->owner);
        mx_printspaces(ml->l_owner - mx_strlen(file->owner) + 2);
    }
    if (c->print_group) {
        mx_printstr(file->group);
        mx_printspaces(ml->l_group - mx_strlen(file->group));
    }
}

static void print_line(t_file *file, t_maxlens_for_print *ml, t_cmd *c) {
    if (!file || !ml || !c)
        return;
    mx_printstr(file->perm);
    mx_print_acl(file->path);
    mx_print_nlink(file, ml);
    mx_printspaces(1);
    print_ow_gr(file, ml, c);
    mx_printspaces(2);
    mx_print_size(file, ml, c);
    mx_printspaces(1);
    mx_print_time(file, c);
    mx_printspaces(1);
    if (c->format_g)
        mx_print_color_name(file);
    else
        mx_printstr(file->filename);
    if (S_ISLNK(file->ffs.st_mode))
        mx_print_linkname(file);
    mx_printstr("\n");
}

void mx_print_long_format(t_list *lf, t_cmd *c) {
    t_maxlens_for_print *ml;

    if (!lf || !c)
        return;
    ml = mx_get_lens_for_print(lf);
    for (t_list *q = lf; q; q = q->next)
        print_line(q->data, ml, c);
    free(ml);
    ml = NULL;
}
