#include "uls.h"

static void print_flags(char flag, t_cmd *c) {
    switch (flag) {
        case 'l':
            c->print_func = long_format;
            break;
        case 'C':
            if (c->print_func != m_format)
                c->print_func = std_format;
            break;
        case '1':
            c->print_func = col_format;
            break;
        case 'm':
            c->print_func = m_format;
            break;
        case 'R':
            c->print_recursion = true;
            break;
    }
}

static void sort_and_time_flags(char flag, t_cmd *c) {
    switch (flag) {
        case 'r':
            c->print_reverse = true;
            break;
        case 'S':
            c->sort_type = sort_size;
            break;
        case 't':
            if (c->sort_type != sort_size)
                c->sort_type = sort_time;
            break;
        case 'c':
            c->time_type = time_ctime;
            break;
        case 'u':
            c->time_type = time_atime;
            break;
    }
}

static void format_flags(char flag, t_cmd *c) {
    switch (flag) {
        case 'a':
            c->print_hidden = true;
            break;
        case 'A':
            c->print_dots_folder = true;
            break;
        case 'f':
            c->print_f = true;
            break;
        case 'G':
            c->format_g = true;
            break;
    }
}

static void filter_flags(char flag, t_cmd *c) {
    switch (flag) {
        case 'h':
            c->format_h = true;
            break;
        case 'T':
            c->format_t = true;
            break;
        case 'g':
            c->print_owner = false;
            break;
        case 'o':
            c->print_group = false;
            break;
        case 'n':
            c->print_owner_group_num = true;
            break;
    }
}

void mx_flags(char flag, t_cmd *c) {
    print_flags(flag, c);
    sort_and_time_flags(flag, c);
    format_flags(flag, c);
    filter_flags(flag, c);
}
