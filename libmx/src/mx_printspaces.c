#include "libmx.h"

void mx_printspaces(int count) {
    if (count > 0)
        for (int i = 0; i < count; i++)
            mx_printchar(' ');
}
