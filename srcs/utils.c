# include "../includes/tester.h"

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

void	free_res(t_result *res)
{
	if (res->answer)
		free(res->answer);
	if (res->error)
		free(res->error);
	if (res->valgrind)
		free(res->valgrind);
	if (res->prompt)
		free(res->prompt);
}