#include "uls.h"

static int get_maxlen_name(t_list *lf) {
    int max = 0;
    int tmp = 0;

    if (!lf)
        return 0;
    for (t_list *q = lf; q != NULL; q = q->next) {
        tmp = mx_strlen(((t_file *)q->data)->filename);
        if (tmp > max)
            max = tmp;
    }
    return max;
}

static t_file **get_names(t_list *list, int size) {
    t_file **result = NULL;
    int i = 0;

    if (!list)
        return NULL;
    result = (t_file **)malloc((size + 1) * sizeof(t_file *));
    for (t_list *q = list; q != NULL; q = q->next, i++)
        result[i] = q->data;
    result[size] = NULL;
    return result;
}

static void print_f_names(t_file **names, int maxlencol, int win) {
    int rows;
    int size;
    int cols = (win / ((8 - (maxlencol % 8)) + maxlencol));

    for (size = 0; names[size]; size++)
    if (!names || !cols || !maxlencol)
        return;
    rows = size / cols;
    if (size % cols)
        rows += 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; i + j < size; j += rows) {
            mx_printstr(names[i + j]->filename);
            if (names[i + j + 1] && (i + j + rows < size))
                mx_print_tab(mx_strlen(names[i + j]->filename), maxlencol);
        }
        mx_printchar('\n');
    }
}

static void print_f_names_g(t_file **names, int maxlencol, int win) {
    int rows;
    int size;
    int cols = win / (maxlencol + 1);

    for (size = 0; names[size]; size++)
    if (!names || !cols || !maxlencol)
        return;
    rows = size / cols;
    if (size % cols)
        rows += 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; i + j < size; j += rows) {
            mx_print_color_name(names[i + j]);
            if (names[i + j + 1] && (i + j + rows < size))
                mx_printspaces(maxlencol + 1
                               - mx_strlen(names[i + j]->filename));
        }
        mx_printchar('\n');
    }
}

void mx_print_std_format(t_list *lf, t_cmd *c) {
    int maxlencol = get_maxlen_name(lf);
    int count_names = mx_list_size(lf);
    t_file **names = get_names(lf, count_names);
    struct winsize win;

    if (!lf || !names)
        return;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (c->format_g)
        print_f_names_g(names, maxlencol, win.ws_col);
    else
        print_f_names(names, maxlencol, win.ws_col);
    free(names);
}
