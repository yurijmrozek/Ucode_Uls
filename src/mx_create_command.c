#include "uls.h"

static t_cmd *initiailze_default();
static void initiailze_default_format(t_cmd *c);
static void check_if_fG_flag(t_cmd *c);

/* *** */

t_cmd *mx_create_command(int argc, char **argv) {
    t_cmd *c = initiailze_default();
    int i = 1;

    initiailze_default_format(c);

    for (; i < argc; i++)
        if (argv[i] && argv[i][0] == '-') {
            if (mx_strcmp(argv[i], "--") == 0)
                break;
            for (int j = 1; j < mx_strlen(argv[i]); j++)
                mx_flags(argv[i][j], c); // flags setup
        }
        else
            break;

    for (; i < argc; i++)
        if (!argv[i]) {
            c->error_null_args = true;
            break;
        }

    check_if_fG_flag(c);

    return c;
}

/* *** */

static void check_if_fG_flag(t_cmd *c) { /* -f do not sort -G no group */
    if (c->print_f == true) {
        c->print_dots_folder = true;
        c->print_hidden = true;
        c->sort_type = sort_none;
    }
    if (!isatty(STDOUT_FILENO))
        c->format_g = false;
}

static t_cmd *initiailze_default() {
    t_cmd *c = (t_cmd *)malloc(sizeof(t_cmd));

    if (isatty(STDOUT_FILENO)) /*STDIN_FILENO это файловый дескриптор STDOUT_FILENO 1*/
        c->print_func = std_format;
    else
        c->print_func = col_format;

    c->sort_type = sort_name;
    c->time_type = time_mtime;
    c->error_null_args = false;
    c->print_recursion = false;  // -R
    c->print_reverse = false;  // -r
    c->print_dots_folder = false;  // -A
    c->print_hidden = false;  // -a
    c->print_f = false;  // -f
    c->print_owner = true;  // -g
    c->print_group = true;  // -o
    c->print_owner_group_num = false;  // -n
    return c;
}

static void initiailze_default_format(t_cmd *c) {
    c->format_h = false;
    c->format_t = false;
    c->format_g = false;
}
