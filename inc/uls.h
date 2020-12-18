#ifndef ULS_H
#define ULS_H

#include "libmx.h"

#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/acl.h>

#define BLK   "\x1B[30m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define RED_B "\x1B[1;31m"
#define RESET_B "\x1B[1;31m"
#define BLK_F_RED_B "\x1B[0;30;41m"
#define BLK_F_CYAN_B "\x1B[0;30;46m"
#define BLOCK "\x1B[0;34;46m"
#define CHR "\x1B[0;34;43m"
#define DIR_T "\x1B[0;30;42m"
#define DIR_X "\033[0;30;43m"

#define FLAGS "ACGRSTacfghlmnortu1"

typedef struct s_uls {
	void *data;
    int len;
	struct s_uls *next;
} t_uls;

typedef struct s_file {
	char *path;  // = dir/filename
	char *filename;  // d_name in readdir
	struct stat ffs;  // stat
	char *owner;
	char *group;
	char *perm;
} t_file;

typedef struct s_maxlens_for_print {
	int l_links;
	int l_owner;
	int l_group;
	int l_size;
} t_maxlens_for_print;

typedef struct s_cmd {
	int print_func;
	int sort_type;
	int time_type;
	bool error_null_args;  // if one of them NULL
	bool print_recursion;  // -R
	bool print_reverse;  // -r
	bool print_dots_folder;  // -A
	bool print_hidden;  // -a
	bool print_f;  // enable -A, -a disable all sortings, -t, -r
	bool print_owner;  // -g
	bool print_group;  // -o
	bool print_owner_group_num;  // -n
	// bool print_blocks;  // -s
	bool format_h;  // -h
	// bool format_at_symbol;  // -@
	// bool format_e;  // -e
	bool format_t;  // -T
	bool format_g;  // G color
} t_cmd;

enum e_time_type {
    time_mtime,  // default
    time_ctime,  // c
    time_atime  // -u 
};

enum e_print_type {
    long_format,  // -l
    std_format,  // -C
    col_format,  // -1
    m_format  // -m
};

enum sort_type{
	sort_none,  // -f
    sort_name,  // default
    sort_size,  // -S
    sort_time,  // -t
};

// -----------------check errors-----------------------
int check_error(int argc, char **argv);

// -----------------check flags-----------------------
t_cmd *mx_create_command(int argc, char **argv);
void mx_flags(char flag, t_cmd *c);

// -----------------get arguments-----------------------
bool mx_isdir(char *filename, t_list *q);
int mx_islink(char *filename, t_list *q);
// 0 - not link, 1 - link to file, 5 - link to folder
bool mx_ishidden(char *filename, t_list *q);
t_list *mx_get_arg_f(int argc, char **argv, int i, t_cmd *c);
t_list *mx_get_arg_d(int argc, char **argv, int i, t_cmd *c);
bool mx_strcmp_f_d_bool(void *d1, void *d2);
t_list *mx_get_files_list_dir(char *dir, t_cmd *c);
t_file *mx_get_filesattr(char *filename, char *directory, t_cmd *c);
void mx_get_permissions(t_file *file);

// -----------------sort functions-----------------------
t_list *mx_sort_uls_list(t_list *list, t_cmd *c,
						bool (*cmp)(void *a, void *b, t_cmd *c));
bool mx_strcmp_names(void *d1, void *d2, t_cmd *c);
bool mx_strcmp_size(void *d1, void *d2, t_cmd *c);
bool mx_strcmp_mtime(void *d1, void *d2, t_cmd *c);
bool mx_strcmp_atime(void *d1, void *d2, t_cmd *c);
bool mx_strcmp_ctime(void *d1, void *d2, t_cmd *c);

// -----------------print functions-----------------------
t_maxlens_for_print *mx_get_lens_for_print(t_list *lf);
void mx_prepare_list_and_print(t_list *lf, t_cmd *c);
void mx_print_long_format(t_list *lf, t_cmd *c);
void mx_print_std_format(t_list *lf, t_cmd *c);
void mx_print_col_format(t_list *lf, t_cmd *c);
void mx_print_m_format(t_list *lf, t_cmd *c);

// -----------------long print-----------------------
void mx_print_total(t_list *lf);
void mx_print_acl(char *file);
void mx_print_nlink(t_file *file, t_maxlens_for_print *ml);
void mx_print_size(t_file *file, t_maxlens_for_print *ml, t_cmd *c);
void mx_print_tab(int len_name, int maxlencol);
char *mx_hr_size(off_t st_size);
int mx_hr_get_pow(off_t st_size);
void mx_hr_write_number(char *size, off_t st_size);
void mx_print_time(t_file *file, t_cmd *c);
void mx_print_color_name(t_file *file);
void mx_print_linkname(t_file *file);

// -----------------clear leaks-----------------------
void mx_clear_filesattr(t_file *file, t_cmd *c);
void mx_clear_filesattr_list(t_list **fl, t_cmd *c);

#endif
