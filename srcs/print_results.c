#include "../includes/tester.h"

void	print_result(t_result *res, t_parameters *p)
{
	if (p->answers)
	{
		if (res->error)
			ft_printf("error : %s\n", res->error);
		else
		{
			if (res->answer)
				ft_printf("answer : %s\n", res->answer);
			else
				ft_printf("answer : %s\n\n", res->answer);
		}
	}
}

int	check_valgrind_errors(t_result *res)
{
	if (res->valgrind)
	{
		if (strstr(res->valgrind, "SUMMARY"))
			return (2);
		else
		{
			ft_printf("valgrind errors : \n%s", res->valgrind);
			return (1);
		}
	}
	return (0);
}
