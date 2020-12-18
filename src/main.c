#include "uls.h"

static void print_one_dir(char *dir, t_cmd *c) {
    t_list *files_list = mx_get_files_list_dir(dir, c);
    t_file *tmp;

    if (files_list == NULL)
        return;
    if (c->print_func == long_format)
        mx_print_total(files_list);
    mx_prepare_list_and_print(files_list, c);
    if (c->print_recursion)  // recursion
        for (t_list *q = files_list; q; q = q->next) {
            tmp = q->data;
            if (mx_isdir(NULL, q) && mx_strcmp(tmp->filename, ".")
                && mx_strcmp(tmp->filename, "..")) {
                mx_printstr("\n");  // get effect on -RA
                mx_printstr(tmp->path);
                mx_printstr(":\n");
                print_one_dir(tmp->path, c);
            }
        }
    mx_clear_filesattr_list(&files_list, c);
}

static void print_files(t_list *f_names, t_list *d_names, t_cmd *c) {
    t_list *files_list = NULL;
    if (f_names) {
        for (t_list *q = f_names; q; q = q->next)
            mx_push_back(&files_list, mx_get_filesattr(q->data, ".", c));

        mx_prepare_list_and_print(files_list, c);
        mx_clear_filesattr_list(&files_list, c);
        
        if (d_names) {
            mx_printstr("\n");
            if (mx_list_size(d_names) == 1 && !c->error_null_args) {
                mx_printstr(d_names->data);
                mx_printstr(":\n");
            }
        }
    }
}

static void print_directories(t_list *d_names, t_cmd *c) {
    if (d_names) {
        if (mx_list_size(d_names) == 1 && c->error_null_args) {
            mx_printstr(d_names->data);
            mx_printstr(":\n");
        }
        for (t_list *q = d_names; q; q = q->next) {
            if (mx_list_size(d_names) != 1) {
                mx_printstr(q->data);
                mx_printstr(":\n");
            }
            print_one_dir(q->data, c);
            if (q->next != NULL)
                mx_printstr("\n");
        }
    }
}

int main(int argc, char **argv) {
    int position = check_error(argc, argv);
    t_cmd *c = mx_create_command(argc, argv);
    t_list *f_names = mx_get_arg_f(argc, argv, position, c);
    t_list *d_names = mx_get_arg_d(argc, argv, position, c);

    print_files(f_names, d_names, c);
    if (!f_names && !d_names && !c->error_null_args)
        mx_push_back(&d_names, ".");
    print_directories(d_names, c);
    return 0;
}
