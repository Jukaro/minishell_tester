#include "../includes/tester.h"

static void	parse_line(t_test *test, char *str)
{
	int		first_arg;
	char	*first_arg_ptr;
	char	*arg;
	char	*tmp;

	first_arg_ptr = ft_strchr(str, '-');
	first_arg = first_arg_ptr ? first_arg_ptr - str : -1;

	test->timeout = 1000;
	test->need_answer = 1;
	test->check_method = CMP;
	test->result = NULL;
	if (first_arg == -1)
	{
		tmp = ft_substr(str, 0, ft_strlen(str) - 1);
		test->cmd = ft_strtrim(tmp, " \t\n");
		free(tmp);
	}
	else
	{
		tmp = ft_substr(str, 0, first_arg);
		test->cmd = ft_strtrim(tmp, " \t\n");
		free(tmp);
		for (int i = 0; str[i]; i++)
		{
			if (str[i] == '-')
			{
				arg = ft_substr(&str[i], 0, ft_strchrset(&str[i], " \t\n") - &str[i]);
				if (!ft_strncmp("-timeout=", arg, 9) && ft_isdigit(str[i + 9]))
					test->timeout = ft_atoi(&str[i + 9]);
				if (!ft_strncmp("-no_answer", arg, 10))
					test->need_answer = 0;
				if (!ft_strncmp("-result=", arg, 8) && ft_isprint(str[i + 8]))
					test->result = get_result(&str[i + 8]);
				if (!ft_strncmp("-check_method=", arg, 14) && ft_isprint(str[i + 14]))
					test->check_method = get_method(&str[i + 14]);
				i += ft_strlen(arg);
				free(arg);
			}
		}
	}
}

void	get_valgrind(char *str, t_parameters *p)
{
	
}

t_test	**parse_testfile(char *file, t_parameters *p)
{
	t_test	**tests;
	t_test	*new_test;
	char	*str;
	int		fd;
	int		id;
	int		nb_tests;

	fd = open(file, O_RDONLY);
	str = "init";
	id = 0;
	tests = malloc(sizeof(t_test *));
	*tests = NULL;
	nb_tests = 1;
	for (int i = 0; str; i++)
	{
		str = get_next_line(fd);
		if (str && strstr(str, "valgrind:"))
			get_valgrind(str, p);
		else if (str && str[0] != '#')
		{
			new_test = ft_testnew();
			new_test->index = nb_tests;
			parse_line(new_test, str);
			ft_testadd_back(tests, new_test);
			nb_tests++;
		}
		if (str)
			free(str);
	}
	close(fd);
	return (tests);
}