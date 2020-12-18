#include "uls.h"

void mx_print_linkname(t_file *file) {
    char link[255];
    int size = 0;

    if (!file)
        return;
    size = readlink(file->path, link, sizeof(link) - 1);
    link[size] = '\0';
    mx_printstr(" -> ");
    mx_printstr(link);
}
