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

typedef struct s_parameters
{
	int	valgrind;
	int	answers;
	int	test;

	int	valg_timeout;
	int	answer_timeout;
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
	int				timeout;
	int				need_answer;
	char			*check_method;
	struct s_test	*next;
}	t_test;

/* ---------------------------------- init ---------------------------------- */

t_parameters	init_parameters(int argc, char **argv);

/* ---------------------------------- utils --------------------------------- */

void			free_double_array(char **array);
void			free_res(t_result *res);

/* ------------------------------ print_results ----------------------------- */

void			print_result(t_result *res, t_parameters *p);
int				check_valgrind_errors(t_result *res);

/* ---------------------------------- tests --------------------------------- */

t_test			*ft_testnew(void);
void			ft_testadd_back(t_test **lst, t_test *new);
void			ft_testclear(t_test **lst);
int				ft_testsize(t_test *lst);

#endif
