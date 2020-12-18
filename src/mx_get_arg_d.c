#include "uls.h"

t_list *mx_get_arg_d(int argc, char **argv, int i, t_cmd *c) {
    t_list *d_argv = NULL;

    for (; i < argc; i++)
        if (argv[i] 
            && mx_isdir(argv[i], NULL))
            mx_push_back(&d_argv, argv[i]);
        else if (argv[i] 
                && (mx_islink(argv[i], NULL) == 5)
                && c->print_func != long_format)
            mx_push_back(&d_argv, argv[i]);

    if(!c->print_f)
        mx_sort_list(d_argv, mx_strcmp_f_d_bool);
        
    return d_argv;
}
