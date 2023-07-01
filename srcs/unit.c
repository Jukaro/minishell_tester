/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:26:54 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/01 19:22:59 by jfarkas          ###   ########.fr       */
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
		usleep(1000);
		gettimeofday(&tv2, NULL);
		elapsed_time = (tv2.tv_sec - tv1.tv_sec) * 1000;
		elapsed_time += (tv2.tv_usec - tv1.tv_usec) / 1000;
		if (elapsed_time > msec)
			timeout = 1;
		new_line = get_next_line(fd);
	}
	// printf("%f ms.\n", elapsed_time);
	str = ft_strjoin(str, new_line);
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
	return (str);
}

t_result	test(int child_in, int child_out, int valg_out, char *cmd, t_parameters p)
{
	t_result	res;
	char	*request;

	res.answer = NULL;
	res.errors = NULL;
	res.valgrind = NULL;
	res.prompt = NULL;
	if (p.test)
		ft_printf("testing %s ...\n", cmd);
	request = ft_strjoin(cmd, "\n");
	ft_putstr_fd(request, child_in);
	res.prompt = get_str_from_fd(child_out, 0, 1000);
	if (res.prompt)
	{
		res.answer = get_str_from_fd(child_out, 1, p.answer_timeout);
		if (p.valgrind)
		{
			if (ft_strncmp(cmd, "exit", 4))
				res.valgrind = get_str_from_fd(valg_out, 1, p.valg_timeout);
			else
				res.valgrind = get_str_from_fd(valg_out, 1, 1000);
		}
	}
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
		// close(valgrind[1]);
		close(request[1]);
		if (execve(cmd_line[0], cmd_line, envp) == -1)
			perror("execve");
		exit(1);
	}
	close(child_out[1]);
	close(child_error[1]);
	close(valgrind[1]);
	// close(valgrind[0]);
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
	t_result	res;

	setup_pipes(request, child_out, child_error, valgrind);
	start_minishell(cmd_line, envp, &pid, request, child_out, child_error, valgrind);

	printf("valgrind[1] : %d\n", valgrind[1]);
	if (p.valgrind)
		print_valgrind_start(child_error[0]);
	for (int i = 0; tests[i]; i++)
	{
		res = test(request[1], child_out[0], child_error[0], tests[i], p);
		if (p.answers)
			ft_printf("answer : %s\n", res.answer);
		if (res.valgrind)
		{
			if (strstr(res.valgrind, "SUMMARY"))
				break ;
			else
				ft_printf("errors : \n%s", res.valgrind);
		}
		if (res.answer)
			free(res.answer);
		if (res.errors)
			free(res.errors);
		if (res.valgrind)
			free(res.valgrind);
		if (res.prompt)
			free(res.prompt);
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
	if (res.answer)
		free(res.answer);
	if (res.errors)
		free(res.errors);
	if (res.valgrind)
		free(res.valgrind);
	if (res.prompt)
		free(res.prompt);
	close(request[1]);
	close(child_out[0]);
	close(child_error[0]);
	close(valgrind[0]);
	waitpid(pid, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
	char	*minishell = "/bin/valgrind --log-fd=10 ./minishell/minishell --leak-check=full";
	char	**cmd_line = ft_split(minishell, ' ');
	char	**tests;
	char	*line;
	int		tests_file;
	t_parameters	p;

	p = init_parameters(argc, argv);

	tests_file = open("test.txt", O_RDONLY);
	tests = ft_split("init", ':');

	struct timeval tv1, tv2;
	double	elapsed_time;
	gettimeofday(&tv1, NULL);

	for (int i = 0; tests[0]; i++)
	{
		free_double_array(tests);
		line = get_next_line(tests_file);
		tests = ft_split(line, ';');
		if (tests[0] && tests[0][0] != '#')
		{
			// ft_printf("\n------ testing line %d ------\n\n", i);
			test_line(cmd_line, tests, envp, p);
		}
		free(line);
	}
	free_double_array(tests);
	free_double_array(cmd_line);
	gettimeofday(&tv2, NULL);
	elapsed_time = (tv2.tv_sec - tv1.tv_sec);
	elapsed_time += (tv2.tv_usec - tv1.tv_usec) / 1000000.0;
	// printf("total : %.3fs.\n", elapsed_time);
	close(tests_file);
	return (0);
}
