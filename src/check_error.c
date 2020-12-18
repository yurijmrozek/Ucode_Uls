#include "uls.h"

static void print_error_flag(char c, char *flag) {
    mx_printerr("uls: illegal option -- ");
    write(2, &c, 1);
    mx_printerr("\nusage: uls [-");
    mx_printerr(flag);
    mx_printerr("] [file ...]\n");
}

static int check_flags(int argc, char **argv) {
    char *flag = FLAGS;
    int len_flag = mx_strlen(flag);
    int i = 1;

    for (; i < argc; i++)
        if (argv[1][0] == '-' && argv[i][0] == '-') {
            if (mx_strcmp(argv[i], "--") == 0)
                break;
            for (int j = 1; j < mx_strlen(argv[i]); j++)
                for (int k = 0; k < len_flag && argv[i][j] != flag[k]; k++)
                    if (k == len_flag - 1) {
                        print_error_flag(argv[i][j], flag);
                        exit(1);
                    }
        }
        else
            break;
    return i;
}

static void print_error_arguments(char *v) {
    mx_printerr("uls: ");
    mx_printerr(v);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    mx_printerr("\n");
}

static void check_arguments(int argc, char **argv, int p) {
    struct stat buff;

    for (int i = p; i < argc; i++) {
        if (argv[i] && (lstat(argv[i], &buff) != 0)) {
            print_error_arguments(argv[i]);
            argv[i] = NULL;
        }
    }
}

int check_error(int argc, char **argv) {
    int position = check_flags(argc, argv);

    if (argv[position] && mx_strcmp(argv[position], "--") == 0)
        position++;
    for (int j = position; j < argc; j++)
        if (argv[j][0] == '-')
            check_arguments(1, &argv[j], 0);

    check_arguments(argc, argv, position);
    return position;
}
