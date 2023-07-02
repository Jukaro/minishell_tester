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

t_parameters	init_parameters(int argc, char **argv);
void			free_double_array(char **array);

#endif
