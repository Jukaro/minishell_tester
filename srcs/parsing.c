#include "../includes/tester.h"

char	*get_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += skip_quotes(&str[i], str[i]);
		i++;
	}
	return (ft_substr(str, 0, i));
}

static void	parse_line(t_test *test, char *str)
{
	int		sep;
	char	*sep_ptr;
	char	*arg;
	char	*tmp;

	sep_ptr = strstr(str, "<<<<>>>>");
	sep = sep_ptr ? sep_ptr - str : -1;

	test->timeout = 1000;
	test->need_answer = 1;
	test->check_method = CMP;
	test->result = NULL;
	test->signal = 0;
	if (sep == -1)
	{
		tmp = ft_substr(str, 0, ft_strlen(str) - 1);
		test->cmd = ft_strtrim(tmp, " \t\n");
		free(tmp);
	}
	else
	{
		tmp = ft_substr(str, 0, sep);
		test->cmd = ft_strtrim(tmp, " \t\n");
		free(tmp);
		for (int i = sep + 8; str[i]; i++)
		{
			if (str[i] == '-')
			{
				arg = get_arg(&str[i]);
				if (!ft_strncmp("-timeout=", arg, 9) && ft_isdigit(str[i + 9]))
					test->timeout = ft_atoi(&str[i + 9]);
				if (!ft_strncmp("-no_answer", arg, 10))
					test->need_answer = 0;
				if (!ft_strncmp("-result=", arg, 8) && ft_isprint(str[i + 8]))
					test->result = get_result(&str[i + 8]);
				if (!ft_strncmp("-check_method=", arg, 14) && ft_isprint(str[i + 14]))
					test->check_method = get_method(&str[i + 14]);
				if (!ft_strncmp("-signal=", arg, 8) && ft_isprint(str[i + 8]))
					test->signal = get_signal(&str[i + 8]);
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
