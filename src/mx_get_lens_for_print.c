#include "uls.h"

static void initialize(t_maxlens_for_print *len) {
    len->l_links = 0;
    len->l_owner = 0;
    len->l_group = 0;
    len->l_size = 0;
}

static void compare_str(int *max, char *str) {
    int c = mx_strlen(str);

    if (*max < c)
        *max = c;
}

static void compare_numb(int *max, int numb) {
    char *tmp = mx_itoa(numb);
    int c = mx_strlen(tmp);

    if (*max < c)
        *max = c;
    free(tmp);
}

t_maxlens_for_print *mx_get_lens_for_print(t_list *lf) {
    t_maxlens_for_print *len;
    t_file *tmp;
    bool majorminor = false;

    if (!lf)
        return NULL;
    len = malloc(sizeof(t_maxlens_for_print));
    initialize(len);
    for (t_list *q = lf; q != NULL; q = q->next) {
        tmp = q->data;
        compare_numb(&len->l_links, tmp->ffs.st_nlink);
        compare_str(&len->l_owner, tmp->owner);
        compare_str(&len->l_group, tmp->group);
        compare_numb(&len->l_size, tmp->ffs.st_size);
        if (S_ISBLK(tmp->ffs.st_mode) || S_ISCHR(tmp->ffs.st_mode))
            majorminor = true;
    }
    if (majorminor)
        len->l_size = len->l_size < 8 ? 8 : len->l_size;
    return len;
}
