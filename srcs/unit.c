/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:26:54 by jfarkas           #+#    #+#             */
/*   Updated: 2023/07/20 12:26:01 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/tester.h"

t_result	test(int child_in, int child_out, int child_error, int valg_out, t_test *test, t_parameters p)
{
	t_result	res;
	char	*request;

	res.answer = NULL;
	res.error = NULL;
	res.valgrind = NULL;
	res.prompt = NULL;
	if (p.test)
		ft_printf("%d - Testing %s ...\n", test->index, test->cmd);
	request = ft_strjoin(test->cmd, "\n");
	// printf("request : %s\n", request);
	ft_putstr_fd(request, child_in);
	free(request);
	// printf("getting prompt.\n");
	if (test->index == 1)
		usleep(100000);
	usleep(20000); // echo lent ??
	res.prompt = get_prompt(child_out, test->cmd, 10);
	printf("prompt : %s\n", res.prompt);
	// if (res.prompt)
	// {
		if (!test->need_answer)
		{
			if (p.valgrind)
			{
				if (!ft_strncmp(test->cmd, "exit", 4))
					res.valgrind = get_str_from_fd(valg_out, 1, p.valg_timeout);
				else
					res.valgrind = get_str_from_fd(valg_out, 1, 50);
			}
			return (res);
		}
		get_answer(child_out, child_error, &res, 1, p.answer_timeout);
		if (p.valgrind)
		{
			if (!ft_strncmp(test->cmd, "exit", 4))
				res.valgrind = get_str_from_fd(valg_out, 1, p.valg_timeout);
			else
				res.valgrind = get_str_from_fd(valg_out, 1, 50);
		}
	// }
	return (res);
}

void	test_line(char **cmd_line, t_test **tests, char **envp, t_parameters p)
{
	pid_t 		pid;
	int			request[2];
	int			child_out[2];
	int			child_error[2];
	int			valgrind[2];
	int			error;
	int			error_count; // a mettre dans struct
	int			tests_nb;
	int			main_valgrind_id;
	t_result	res;

	start_minishell(cmd_line, envp, &pid, request, child_out, child_error, valgrind);
	usleep(500 * 1000);
	error_count = 0;
	tests_nb = ft_testsize(*tests);
	if (p.valgrind)
		main_valgrind_id = print_valgrind_start(valgrind[0]);
	for (t_test *ptr = *tests; ptr; ptr = ptr->next)
	{
		res = test(request[1], child_out[0], child_error[0], valgrind[0], ptr, p);
		print_result(&res, &p);
		error = check_valgrind_errors(&res, main_valgrind_id, valgrind[0]);
		if (error == 2)
			break ;
		else if (error)
			error_count++;
		// printf("test val : %s\n", get_str_from_fd(valgrind[0], 1, 10));
		// printf("test std : %s\n", get_str_from_fd(child_out[0], 1, 10));
		// printf("test err : %s\n", get_str_from_fd(child_error[0], 1, 10));
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

int main(int argc, char **argv, char **envp)
{
	// char	*minishell = "/bin/valgrind --log-fd=9  --leak-check=full ./minishell/minishell";
	// char	*minishell = "/bin/valgrind --log-fd=9 /bin/bash -i"; // mettre le fd dynamiquement
	// char	*minishell = "/bin/bash -i"; // mettre le fd dynamiquement
	char	*minishell = "/bin/valgrind --log-fd=9 --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=../minishell/vsupp ./minishell/minishell_damien";
	// char	*minishell = "/bin/valgrind --log-fd=9 --leak-check=full --show-leak-kinds=all --suppressions=../minishell/vsupp /bin/bash -i";
	char	**cmd_line = ft_split(minishell, ' ');
	char	*line;
	int		tests_file;
	t_test	**tests;
	int		tests_nb;
	t_parameters	p;

	struct timeval tv1, tv2;
	double	elapsed_time;
	gettimeofday(&tv1, NULL);

	p = init_parameters(argc, argv);

	// gerer les signaux SIGINT et autres

	tests = parse_testfile("test.txt", &p);
	test_line(cmd_line, tests, envp, p);
	// for (int i = 0; i < tests_nb; i++)
	// {
	// 	// ft_printf("\n------ testing line %d ------\n\n", i);
	// 	test_line(cmd_line, tests2, envp, p);
	// }
	// id valgrind pour afficher valgrind trace childs
	// fork pour plusieurs fichiers en même temps
	// regler conditional jump valgrind
	// faire un "send" pour envoyer des trucs à cat / heredoc
	// verifier si minishell vivant sans valgrind et summary
	ft_testclear(tests);
	free(tests);
	free_double_array(cmd_line);
	gettimeofday(&tv2, NULL);
	elapsed_time = (tv2.tv_sec - tv1.tv_sec);
	elapsed_time += (tv2.tv_usec - tv1.tv_usec) / 1000000.0;
	printf("total : %.3fs.\n", elapsed_time);
	close(tests_file);
	return (0);
}
