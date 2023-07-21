#ifndef TESTER_H
# define TESTER_H

# include <stdio.h>
# include <unistd.h>
# include <memory.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <errno.h>

# include "../libft/libft.h"

# define CMP 0
# define FIND 1

typedef struct s_parameters
{
	int		valgrind;
	int		answers;
	int		test;

	int		valg_timeout;
	int		answer_timeout;
	char	*valgrind_line;
}	t_parameters;

typedef struct s_result
{
	char	*prompt;
	char	*answer;
	char	*valgrind;
	char	*error;
}	t_result;

typedef struct	s_test
{
	char			*cmd;
	char			*result;
	int				timeout;
	int				need_answer;
	int				check_method;
	int				index;
	struct s_test	*next;
}	t_test;

/* ---------------------------------- init ---------------------------------- */

t_parameters	init_parameters(int argc, char **argv);

/* ---------------------------------- setup --------------------------------- */

void			start_minishell(char **cmd_line, char **envp, pid_t *pid, int request[2], int child_out[2], int child_error[2], int valgrind[2]);

/* ---------------------------------- utils --------------------------------- */

void			free_double_array(char **array);
void			free_res(t_result *res);
int				get_valgrind_id(char *str);
char			*get_str_from_fd(int fd, int mult_lines, int msec);

/* ------------------------------- read_pipes ------------------------------- */

void			get_answer(int std_fd, int error_fd, t_result *res, int mult_lines, int msec);
char			*get_str_from_fd(int fd, int mult_lines, int msec);
int				print_valgrind_start(int valg_out);
char			*get_prompt(int fd, char *cmd, int msec);

/* ------------------------------ print_results ----------------------------- */

void			print_result(t_result *res, t_parameters *p);
int				check_valgrind_errors(t_result *res, int main_id, int valg_out);

/* ---------------------------------- tests --------------------------------- */

t_test			*ft_testnew(void);
void			ft_testadd_back(t_test **lst, t_test *new);
void			ft_testclear(t_test **lst);
int				ft_testsize(t_test *lst);

/* --------------------------------- parsing -------------------------------- */

int				get_method(char *str);
char			*ft_strchrset(char *str, char *set);
int				is_in_set(char c, char *charset);
int				skip_quotes(char *str, char quote);
char			*get_result(char *str);
t_test			**parse_testfile(char *file, t_parameters *p);

#endif
