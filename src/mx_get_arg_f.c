#include "uls.h"

t_list *mx_get_arg_f(int argc, char **argv, int i, t_cmd *c) {
    t_list *f_argv = NULL;

    for (;i < argc; i++)
        if (argv[i] 
            && !mx_isdir(argv[i], NULL)
            && mx_islink(argv[i], NULL) != 5)
            mx_push_back(&f_argv, argv[i]);
        else if (argv[i] 
                && (mx_islink(argv[i], NULL) == 5)
                && c->print_func == long_format)
            mx_push_back(&f_argv, argv[i]);

    if (!c->print_f)
        mx_sort_list(f_argv, mx_strcmp_f_d_bool);
        
    return f_argv;
}

