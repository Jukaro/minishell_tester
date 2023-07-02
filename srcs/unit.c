/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:26:54 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/02 23:13:34 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/tester.h"

char	*ft_strnjoin(void *dummy, ...)
{
	char	*join;
	char	*to_free;
	char	*str_to_join;
	va_list args;

	join = NULL;
	str_to_join = "init";
	va_start(args, dummy);
	for (int i = 0; str_to_join; i++)
	{
		to_free = join;
		str_to_join = va_arg(args, char *);
		ft_strlen(str_to_join);
		if (str_to_join)
			join = ft_strjoin(join, str_to_join);
		if (to_free && str_to_join)
			free(to_free);
	}
	va_end(args);
	return (join);
}

void	print_valgrind_start(int valg_out)
{
	char	*valgrind;

	valgrind = NULL;
	while (!valgrind)
		valgrind = get_next_line(valg_out);
	ft_printf("valgrind start :\n");
	while (valgrind)
	{
		ft_printf("%s", valgrind);
		free(valgrind);
		valgrind = get_next_line(valg_out);
	}
	free(valgrind);
}

char	*get_str_from_fd(int fd, int mult_lines, int msec)
{
	char	*str;
	char	*tmp;
	char	*new_line;
	struct timeval tv1, tv2;
	double	elapsed_time;
	int		timeout;

	str = NULL;
	tmp = NULL;
	new_line = NULL;
	gettimeofday(&tv1, NULL);
	timeout = 0;
	while (!new_line && !timeout)
	{
		gettimeofday(&tv2, NULL);
		elapsed_time = (tv2.tv_sec - tv1.tv_sec) * 1000;
		elapsed_time += (tv2.tv_usec - tv1.tv_usec) / 1000;
		if (elapsed_time > msec)
			timeout = 1;
		new_line = get_next_line(fd);
		usleep(1000);
	}
	// printf("%f ms.\n", elapsed_time);
	str = ft_strjoin(str, new_line);
	usleep(500);
	while (new_line && mult_lines)
	{
		usleep(100);
		if (new_line)
			free(new_line);
		tmp = str;
		new_line = get_next_line(fd);
		if (new_line)
			str = ft_strjoin(str, new_line);
		if (tmp && str != tmp)
			free(tmp);
	}
	if (new_line)
		free(new_line);
	// printf("str : %s\n", str);
	return (str);
}

t_result	test(int child_in, int child_out, int child_error, int valg_out, char *cmd, t_parameters p)
{
	t_result	res;
	char	*request;

	res.answer = NULL;
	res.error = NULL;
	res.valgrind = NULL;
	res.prompt = NULL;
	if (p.test)
		ft_printf("testing %s ...\n", cmd);
	request = ft_strjoin(cmd, "\n");
	ft_putstr_fd(request, child_in);
	// printf("getting prompt.\n");
	// res.prompt = get_str_from_fd(child_out, 0, 1000);
	// if (res.prompt)
	// {
		res.answer = get_str_from_fd(child_out, 1, p.answer_timeout);
		res.error = get_str_from_fd(child_error, 1, 0);
		if (p.valgrind)
		{
			if (ft_strncmp(cmd, "exit", 4))
				res.valgrind = get_str_from_fd(valg_out, 1, p.valg_timeout);
			else
				res.valgrind = get_str_from_fd(valg_out, 1, 1000);
		}
	// }
	free(request);
	return (res);
}

void	start_minishell(char **cmd_line, char **envp, pid_t *pid, int request[2], int child_out[2], int child_error[2], int valgrind[2])
{
	if ((*pid = fork()) == -1)
		perror("fork");
	if (*pid == 0)
	{
		dup2(child_out[1], 1);
		close(child_out[1]);
		close(child_out[0]);
		dup2(child_error[1], 2);
		close(child_error[1]);
		close(child_error[0]);
		close(valgrind[0]);
		close(request[1]);
		if (execve(cmd_line[0], cmd_line, envp) == -1)
			perror("execve");
		exit(1);
	}
	close(child_out[1]);
	close(child_error[1]);
	close(valgrind[1]);
}

void	setup_pipes(int request[2], int child_out[2], int child_error[2], int valgrind[2])
{
	pipe(request);
	dup2(request[0], 0);
	close(request[0]);

	pipe(child_out);
	pipe(child_error);
	pipe(valgrind);
	fcntl(child_out[0], F_SETFL, O_NONBLOCK);
	fcntl(child_error[0], F_SETFL, O_NONBLOCK);
	fcntl(valgrind[0], F_SETFL, O_NONBLOCK);
}

void	test_line(char **cmd_line, char **tests, char **envp, t_parameters p)
{
	pid_t 		pid;
	int			request[2];
	int			child_out[2];
	int			child_error[2];
	int			valgrind[2];
	int			error;
	int			error_count; // a mettre dans struct
	t_result	res;

	setup_pipes(request, child_out, child_error, valgrind);
	start_minishell(cmd_line, envp, &pid, request, child_out, child_error, valgrind);

	error_count = 0;
	// printf("valgrind[1] : %d\n", valgrind[1]);
	if (p.valgrind)
		print_valgrind_start(valgrind[0]);
	for (int i = 0; tests[i]; i++)
	{
		res = test(request[1], child_out[0], child_error[0], valgrind[0], tests[i], p);
		print_result(&res, &p);
		error = check_valgrind_errors(&res);
		if (error == 2)
			break ;
		else if (error)
			error_count++;
		free_res(&res);
	}
	if (res.valgrind)
	{
		if (strstr(res.valgrind, "Process terminating"))
			ft_printf("crash : \n");
		else
			ft_printf("valgrind end : \n");
		ft_printf("%s", res.valgrind);
	}
	// si exit ne close pas ?
	free_res(&res);
	close(request[1]);
	close(child_out[0]);
	close(child_error[0]);
	close(valgrind[0]);
	waitpid(pid, NULL, 0);
}

char	*ft_strchrset(char *str, char *set)
{
	for (int i = 0; str[i]; i++)
		for (int j = 0; set[j]; j++)
			if (str[i] == set[j])
				return (&str[i]);
	return (NULL);
}

void	parse_line(t_test *test, char *str)
{
	int	first_arg;
	char	*first_arg_ptr;
	char	*arg;

	first_arg_ptr = ft_strchr(str, '-');
	first_arg = first_arg_ptr ? first_arg_ptr - str : -1;

	test->timeout = 1000;
	test->need_answer = 1;
	test->check_method = "cmp";
	if (first_arg == -1)
		test->cmd = ft_substr(str, 0, ft_strlen(str) - 1);
	else
	{
		test->cmd = ft_substr(str, 0, first_arg);
		for (int i = 0; str[i]; i++)
		{
			if (str[i] == '-')
			{
				arg = ft_substr(&str[i], 0, ft_strchrset(&str[i], " \t\n") - &str[i]);
				if (!ft_strncmp("-timeout=", arg, 9) && ft_isdigit(str[i + 9]))
				{
					test->timeout = ft_atoi(&str[i + 9]);
					printf("atoi : %d\n", ft_atoi(&str[i + 9]));
					printf("timeout : %d\n", test->timeout);
				}
				i += ft_strlen(arg);
				free(arg);
			}
		}
	}
}

t_test	**parse_testfile(char *file)
{
	t_test	**tests;
	t_test	*new_test;
	char	*str;
	int		fd;
	int		id;

	fd = open(file, O_RDONLY);
	str = "init";
	id = 0;
	tests = malloc(sizeof(t_test *));
	*tests = NULL;
	for (int i = 0; str; i++)
	{
		str = get_next_line(fd);
		if (str && str[0] != '#')
		{
			new_test = ft_testnew();
			parse_line(new_test, str);
			ft_testadd_back(tests, new_test);
		}
		if (str)
			free(str);
	}
	close(fd);
	return (tests);
}

int main(int argc, char **argv, char **envp)
{
	// char	*minishell = "/bin/valgrind --log-fd=10 ./minishell/minishell --leak-check=full";
	char	*minishell = "/bin/valgrind --log-fd=10 /bin/bash";
	char	**cmd_line = ft_split(minishell, ' ');
	char	**tests;
	char	*line;
	int		tests_file;
	t_test	**tests2;
	t_parameters	p;

	p = init_parameters(argc, argv);

	tests2 = parse_testfile("test.txt");

	t_test	*ptr;

	ptr = *tests2;
	for ( ; ptr; ptr = ptr->next)
		printf("str : %s\n", ptr->cmd);
	ft_testclear(tests2);
	free(tests2);
	// tests_file = open("test.txt", O_RDONLY);
	// tests = ft_split("init", ':');

	struct timeval tv1, tv2;
	double	elapsed_time;
	gettimeofday(&tv1, NULL);

	// for (int i = 0; tests[0]; i++)
	// {
	// 	free_double_array(tests);
	// 	line = get_next_line(tests_file);
	// 	tests = ft_split(line, ';');
	// 	if (tests[0] && tests[0][0] != '#')
	// 	{
	// 		// ft_printf("\n------ testing line %d ------\n\n", i);
	// 		// test_line(cmd_line, tests, envp, p);
	// 	}
	// 	free(line);
	// }
	// free_double_array(tests);
	free_double_array(cmd_line);
	gettimeofday(&tv2, NULL);
	elapsed_time = (tv2.tv_sec - tv1.tv_sec);
	elapsed_time += (tv2.tv_usec - tv1.tv_usec) / 1000000.0;
	printf("total : %.3fs.\n", elapsed_time);
	close(tests_file);
	return (0);
}
