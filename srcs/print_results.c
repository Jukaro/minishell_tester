#include "../includes/tester.h"

void	print_result(t_result *res, t_parameters *p)
{
	if (p->answers)
	{
		if (res->error)
			ft_printf("error : \n%s\n", res->error);
		else
		{
			if (res->answer)
				ft_printf("answer : \n%s\n", res->answer);
			else
				ft_printf("answer : \n%s\n\n", res->answer);
		}
	}
}

int	check_valgrind_errors(t_result *res, int main_id, int valg_out)
{
	if (res->valgrind)
	{
		if (strstr(res->valgrind, "SUMMARY") && get_valgrind_id(res->valgrind) == main_id)
			return (2);
		else if (strstr(res->valgrind, "SUMMARY"))
		{
			ft_printf("child's valgrind end : \n%s\n", res->valgrind);
			return (1);
		}
		else
		{
			if (strstr(res->valgrind, "Memcheck"))
			{
				printf("child's valgrind start :\n%s\n", res->valgrind);
				free(res->valgrind);
				res->valgrind = get_str_from_fd(valg_out, 1, 50);
			}
			ft_printf("child's valgrind end : \n%s\n", res->valgrind);
			return (1);
		}
	}
	return (0);
}
