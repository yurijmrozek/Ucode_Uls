#include "uls.h"

static void get_path(t_file *file, char *dir) {
    char *tmp = NULL;

    if (!file || !dir)
    return;
    if (file->filename[0] == '/' || dir[0] == 0) {
        file->path = mx_strdup(file->filename);
    }
    else {
        tmp = mx_strjoin(dir, "/");
        file->path = mx_strjoin(tmp, file->filename);
        free(tmp);
    }
}

static void get_owner_group(t_file *file, struct stat fs, t_cmd *c) {
    struct passwd *pw;
    struct group *grp;

    pw = getpwuid(fs.st_uid);
    if (pw->pw_name != NULL && !(c->print_owner_group_num))
        file->owner = mx_strdup(pw->pw_name);
    else {
        file->owner = mx_itoa(fs.st_uid);
    }
    grp = getgrgid(fs.st_gid);
    if (grp != NULL && !(c->print_owner_group_num))
        file->group = mx_strdup(grp->gr_name);
    else {
        file->group = mx_itoa(fs.st_gid);
    }
}

t_file *mx_get_filesattr(char *filename, char *directory, t_cmd *c) {
    t_file *file = NULL;
    struct stat fs; /* pointer to the structure that receives results */

    if (!filename || !directory || !c)
        return file;
    file = malloc(sizeof(t_file));
    file->filename = mx_strdup(filename);
    get_path(file, directory);
    lstat(file->path, &fs);
    file->ffs = fs;

    if (c->print_func == long_format) {
        mx_get_permissions(file);
        get_owner_group(file, fs, c);
    }
    else if (c->format_g)
    mx_get_permissions(file);

    return file;
}
