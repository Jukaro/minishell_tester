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
	{
		free(res->answer);
		res->answer = NULL;
	}
	if (res->error)
	{
		free(res->error);
		res->error = NULL;
	}
	if (res->valgrind)
	{
		free(res->valgrind);
		res->valgrind = NULL;
	}
	if (res->prompt)
	{
		free(res->prompt);
		res->prompt = NULL;
	}
}

int		get_valgrind_id(char *str)
{
	int		i;
	char	*str_id;
	int		id;

	i = 0;
	while (str[i + 2] && str[i + 2] != '=')
		i++;
	str_id = ft_substr(str + 2, 0, i);
	id = ft_atoi(str_id);
	free(str_id);
	return (id);
}
