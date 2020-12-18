#include "uls.h"

void mx_print_tab(int len_name, int maxlencol) {
    int count;
    int p;

    for (p = 1; ; p++) {
        if (maxlencol < (p * 8 - 1))
            break;
    }
    count = p * 8 - len_name;
    for (int i = 0; i < count; i += 8)
        mx_printchar('\t');
}
