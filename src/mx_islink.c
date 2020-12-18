#include "uls.h"

int mx_islink(char *filename, t_list *q) {
    struct stat fs;
    int size = 0;
    char link[255];

    if (filename && !q)
        lstat(filename, &fs);
    else if (!filename && q)
        lstat(((t_file *)q->data)->path, &fs);

    if (S_ISLNK(fs.st_mode)) {
        size = readlink(filename, link, sizeof(link) - 1);
        link[size] = '\0';
        if (mx_isdir(link, NULL))
            return 5;
        else
            return 1;
    }
    else
        return 0;
}

