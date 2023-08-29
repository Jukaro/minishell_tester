#include "../includes/tester.h"

void	print_expected(t_test *test, t_result *res, t_parameters *p)
{
	if (test->check_method == CMP)
	{
		if (test->result && res->answer)
		{
			if (!ft_strncmp(test->result, res->answer, ft_strlen(res->answer) - 1))
				printf("\033[38;5;2mresult : OK\033[39m\n");
			else
				printf("\033[38;5;1mresult : KO\033[39m\n");
		}
	}
}

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

static void	check_leaks(char *valgrind)
{
	if (ft_strnstr(valgrind, "Process terminating", ft_strlen(valgrind + 1)))
	{
		printf("\033[38;5;1mvalgrind child : CRASH\033[39m\n");
		return ;
	}
	if (!ft_strnstr(valgrind, "definitely lost: 0", ft_strlen(valgrind) + 1)
		|| !ft_strnstr(valgrind, "indirectly lost: 0", ft_strlen(valgrind) + 1)
		|| !ft_strnstr(valgrind, "possibly lost: 0", ft_strlen(valgrind) + 1)
		|| !ft_strnstr(valgrind, "still reachable: 0", ft_strlen(valgrind) + 1))
		printf("\033[38;5;1mvalgrind child : LEAKS\033[39m\n");
}

int	check_valgrind_errors(t_result *res, int main_id, int valg_out)
{
	if (res->valgrind)
	{
		if (strstr(res->valgrind, "SUMMARY") && get_valgrind_id(res->valgrind) == main_id)
		{
			check_leaks(res->valgrind);
			return (2);
		}
		else if (strstr(res->valgrind, "SUMMARY"))
		{
			ft_printf("child's valgrind end : \n%s\n", res->valgrind);
			check_leaks(res->valgrind);
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
			else
			{
				ft_printf("child's valgrind end : \n%s\n", res->valgrind);
				check_leaks(res->valgrind);
			}
			return (1);
		}
	}
	return (0);
}
