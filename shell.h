#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int nm;
	char *sr;
	struct liststr *next;
} list_t;

typedef struct passdata
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; 
	int cmd_buf_type; 
	int readfd;
	int histcount;
} data_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct built_in - contains a built-in string and funcs
 *@type: the built-in command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_table;


/* looped_shell.c */
int hsh(data_t *, char **);
int find_built_in_func(data_t *);
void find_cmd_func(data_t *);
void cmd_fork_func(data_t *);

/* Cmd.c */
int _is_cmd(data_t *, char *);
char *_duplicate_char(char *, int, int);
char *_Find_path(data_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* Put.c */
void _Put(char *);
int _Putchar(char);
int _PutDf(char c, int fd);
int _Put_str_input(char *str, int D);

/* Strings_func.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *begin_func(const char *, const char *);
char *_strcat(char *, char *);

/* String_func2.c */
char *_strcpy(char *, char *);
char *_str_dupl(const char *);
void _put_input(char *);
int _putchar(char);

/* string_funcs.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* split_func.c */
char **strtoi(char *, char *);
char **strtoi_2(char *, char);

/* Allocation.c */
char *_memset_func(char *, char, unsigned int);
void free_func(char **);
void *_realloc_func(void *, unsigned int, unsigned int);

/* Free_memory.c */
int Bfree(void **);

/* checks_atoi.c */
int interactive(data_t *);
int is_delimeter(char, char *);
int _is_alpha(int);
int _atoi(char *);

/* eroor_funcs.c */
int _convert_func(char *);
void error_print_msg(data_t *, char *);
int prints_dc(int, int);
char *convert_num(long int, int, int);
void delete_comments(char *);

/* Built-in_func.c */
int _exit_function(data_t *);
int _Cd_func(data_t  *);
int _help_func(data_t *);

/* bult-in_func2.c */
int _History_func(data_t *);
int _alias_func(data_t *);

/*get_line.c */
ssize_t Get_Input(data_t *);
int _getline(data_t *, char **, size_t *);
void sigintHandler(int);

/* Get_data.c */
void clear_data(data_t *);
void set_data(data_t *, char **);
void free_data(data_t *, int);

/* Environment_func1.c */
char *_Env_func(data_t *, const char *);
int _Get_env_func(data_t *);
int _New_env_var(data_t *);
int _UNSET_env_func(data_t *);
int _Env_List(data_t *);

/* Environment_func2.c */
char **Get_env(data_t *);
int _unsetenv(data_t *, char *);
int _setenv(data_t *, char *, char *);

/* history2_func.c */
char *Get_history_func(data_t *data);
int Write_history_func(data_t *data);
int Read_history_func(data_t *data);
int Build_history_func(data_t *data, char *buff, int linecounter);
int Re_number_hst_func(data_t *data);

/* LISTES.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* LISTESSEC2.c */
size_t list_length(const list_t *);
char **list_to_str(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Others.c */
int is_chain_d_func(data_t *, char *, size_t *);
void check_ch_func(data_t *, char *, size_t *, size_t, size_t);
int replace_alias_func(data_t *);
int var_replace(data_t *);
int string_replace(char **, char *);

#endif

