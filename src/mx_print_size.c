#include "uls.h"

static void kostyl_minor(t_file *file, int *c) {
    if (!mx_strcmp(file->filename, "autofs_homedirmounter")
        || !mx_strcmp(file->filename, "autofs_notrigger")
        || !mx_strcmp(file->filename, "autofs_nowait")
        || !mx_strcmp(file->filename, "dtrace")) {
        *c = *c - 3;
    }
    else return;
}

static char *get_minor(int minornum) {
    char *minor;
    char *tmp = NULL;

    if (minornum > 256) {
        minor = mx_strnew(10);
        mx_strcpy(minor, "0x00000000");
        tmp = mx_nbr_to_hex(minornum);
        mx_strcpy(minor + (10 - mx_strlen(tmp)), tmp);
        free(tmp);
    }
    else
        minor = mx_itoa(minornum);
    return minor;
}

static void major_minor(t_file *file) {
    int tmp;
    char *major;
    char *minor;

    major = mx_itoa((file->ffs.st_rdev >> 24) & 0xffffff);
    tmp = (file->ffs.st_rdev & 0xffffff);
    if (file->filename[0] == 'a' || file->filename[0] == 'd')
        kostyl_minor(file, &tmp);
    minor = get_minor(tmp);
    mx_printspaces(3 - mx_strlen(major));
    mx_printstr(major);
    mx_printstr(", ");
    mx_printspaces(3 - mx_strlen(minor));
    mx_printstr(minor);
    free(major);
    free(minor);
}

void mx_print_size(t_file *file, t_maxlens_for_print *ml, t_cmd *c) {
    char *tmp;

    if (!file || !ml)
        return;
    if (S_ISBLK(file->ffs.st_mode) || S_ISCHR(file->ffs.st_mode)) {
        major_minor(file);
        c->format_h = false;
    }
    else {
        if (c->format_h) {
            mx_printspaces(1);
            tmp = mx_hr_size(file->ffs.st_size);
            mx_printstr(tmp);
            free(tmp);
        }
        else {
            tmp = mx_itoa(file->ffs.st_size);
            mx_printspaces(ml->l_size - mx_strlen(tmp));
            mx_printstr(tmp);
            free(tmp);
        }
    }
}
