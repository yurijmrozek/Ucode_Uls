#include "uls.h"

bool mx_isdir(char *filename, t_list *q) {
    struct stat fs;

    if (filename && !q) {
        lstat(filename, &fs);
        return (S_ISDIR(fs.st_mode) ? true : false);
    }
    else if (!filename && q){
        lstat(((t_file *)q->data)->path, &fs);
        return (S_ISDIR(fs.st_mode) ? true : false);
    }
    else
        return false;
}

