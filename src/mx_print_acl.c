#include "uls.h"

void mx_print_acl(char *file) {
    char character;
    ssize_t xattr;
    acl_t acl;

    xattr = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
    acl = acl_get_file(file, ACL_TYPE_EXTENDED);
    if (xattr > 0)
        character = '@';
    else if (acl == NULL)
        character = ' ';
    else
        character = '+';
    acl_free(acl);
    mx_printchar(character);
}

