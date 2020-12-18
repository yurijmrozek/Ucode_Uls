#include "uls.h"

t_list *mx_sort_uls_list(t_list *list, t_cmd *c,
                         bool (*cmp)(void *a, void *b, t_cmd *c)) {
    t_list *tmp = NULL;
    t_list *store = list;
    void *swap_data;

    while (list) {
        tmp = store;
        while (tmp) {
            if (tmp->next && cmp(tmp->data, tmp->next->data, c)) {
                swap_data = tmp->data;
                tmp->data = tmp->next->data;
                tmp->next->data = swap_data;
            }
            tmp = tmp->next;
        }
        list = list->next;
    }
    return tmp;
}
