#include "uls.h"

static char *get_type(t_file *file, char *res) {
    res[0] = S_ISBLK(file->ffs.st_mode) ? 'b' :
             S_ISCHR(file->ffs.st_mode) ? 'c' :
             S_ISDIR(file->ffs.st_mode) ? 'd' :
             S_ISSOCK(file->ffs.st_mode) ? 's' :
             S_ISFIFO(file->ffs.st_mode) ? 'p' :
             S_ISLNK(file->ffs.st_mode) ? 'l' : '-';
    return res;
}

void mx_get_permissions(t_file *file) {
    char *res = mx_strnew(10);

    get_type(file, res);
    res[1] = (S_IRUSR & file->ffs.st_mode) ? 'r' : '-';
    res[2] = (S_IWUSR & file->ffs.st_mode) ? 'w' : '-';
    res[3] = (file->ffs.st_mode & S_IXUSR) ?
             ((file->ffs.st_mode & S_ISUID) ? 's' : 'x') :
             ((file->ffs.st_mode & S_ISUID) ? 'S' : '-');
    res[4] = (S_IRGRP & file->ffs.st_mode) ? 'r' : '-';
    res[5] = (S_IWGRP & file->ffs.st_mode) ? 'w' : '-';
    res[6] = (file->ffs.st_mode & S_IXGRP) ?
             ((file->ffs.st_mode & S_ISGID) ? 's' : 'x') :
             ((file->ffs.st_mode & S_ISGID) ? 'S' : '-');
    res[7] = (S_IROTH & file->ffs.st_mode) ? 'r' : '-';
    res[8] = (S_IWOTH & file->ffs.st_mode) ? 'w' : '-';
    res[9] = (file->ffs.st_mode & S_IXOTH) ?
             ((file->ffs.st_mode & S_ISTXT) ? 't' : 'x') :
             ((file->ffs.st_mode & S_ISTXT) ? 'T' : '-');
    file->perm = mx_strdup(res);
    free(res);
}
