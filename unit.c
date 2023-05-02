/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:26:54 by jfarkas           #+#    #+#             */
/*   Updated: 2023/05/02 20:20:16 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# include <unistd.h>
# include <memory.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/select.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <errno.h>
# include <poll.h>

typedef struct s_parameters
{
	int	valgrind;
}	t_parameters;

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

int	wait_fd(int fd, int sec, int msec)
{
	struct timeval tv;
	fd_set rfds;

	tv.tv_sec = sec;
	tv.tv_usec = msec;
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);
	(void)select(fd + 1, &rfds, NULL, NULL, &tv);

	if (FD_ISSET(fd, &rfds))
		return (1);
	else
		return (0);
}

void	print_valgrind(int valg_out, int sec, int msec, char *to_print)
{
	char	*valgrind;
	int		valgrind_error;

	valgrind_error = 0;
	valgrind = "init";
	while (valgrind && wait_fd(valg_out, sec, msec))
	{
		/*if (poll(&(struct pollfd){ .fd = valg_out, .events = POLLIN }, 1, msec) == 1)
		{*/
			valgrind = get_next_line(valg_out);
		//}
		if (valgrind)
		{
			if (!valgrind_error)
			{
				ft_printf("%s", to_print);
				valgrind_error = 1;
			}
			ft_printf("%s", valgrind);
		}
	}
	if (!valgrind_error)
		ft_printf("no valgrind errors.\n");
}

void	print_valgrind_start(int valg_out)
{
	char	*valgrind;

	ft_printf("valgrind start :\n");
	for (int i = 0; i < 5; i++)
	{
		valgrind = get_next_line(valg_out);
		ft_printf("%s", valgrind);
	}
}

int	test(int child_in, int child_out, int valg_out, char *test, t_parameters *p)
{
	char	*request;
	char	*answer;

	ft_printf("testing %s ...\n", test);
	request = ft_strjoin(test, "\n");
	ft_putstr_fd(request, child_in);
	answer = get_next_line(child_out);
	if (answer)
		ft_printf("line received : %s", answer);
	else
	{
		ft_printf("line not received.\n"); // print valgrind pour le test precedent
		return (1);
	}
	answer = get_next_line(child_out);
	if (answer)
	{
		ft_printf("answer : %s", answer);
		if (ft_strncmp(test, "exit", 5) && p->valgrind)
			print_valgrind(valg_out, 0, 100000, "valgrind errors : \n");
	}
	else
		ft_printf("no answer.\n");
	return (0);
}

void	start_minishell(char **cmd_line, char **envp, pid_t *pid, int pfd[2], int pfd2[2], int pfdvalg[2])
{
	if ((*pid = fork()) == -1)
		perror("fork");
	if (*pid == 0)
	{
		dup2(pfd2[1], 1);
		close(pfd2[1]);
		close(pfd2[0]);
		dup2(pfdvalg[1], 2);
		close(pfdvalg[1]);
		close(pfdvalg[0]);
		close(pfd[1]);
		if (execve(cmd_line[0], cmd_line, envp) == -1)
			perror("execve");
		exit(1);
	}
	close(pfd2[1]);
	close(pfdvalg[1]);
}

void	setup_pipes(int pfd[2], int pfd2[2], int pfdvalg[2])
{
	pipe(pfd);
	dup2(pfd[0], 0);
	close(pfd[0]);

	pipe(pfd2);
	pipe(pfdvalg);
}

int main(int argc, char **argv, char **envp)
{
	pid_t 	pid;
	int		pfd[2];
	int		pfd2[2];
	int		pfdvalg[2];
	char	*minishell = "/bin/valgrind ./test";
	char	**cmd_line = ft_split(minishell, ' ');
	char	**tests = ft_split("sfdgufds:segfault:invalid write:lol:exit", ':');
	t_parameters p;

	p.valgrind = 1;
	setup_pipes(pfd, pfd2, pfdvalg);
	start_minishell(cmd_line, envp, &pid, pfd, pfd2, pfdvalg);

	print_valgrind_start(pfdvalg[0]);
	for (int i = 0; tests[i]; i++)
		if (test(pfd[1], pfd2[0], pfdvalg[0], tests[i], &p))
			break ;
	// si exit ne close pas ?
	print_valgrind(pfdvalg[0], 0, 100000, "valgrind end : \n");
	close(pfd[1]);
	close(pfd2[0]);
	close(pfdvalg[0]);
	waitpid(pid, NULL, 0);

	// setup_pipes(pfd, pfd2, pfdvalg);
	// start_minishell(cmd_line, envp, &pid, pfd, pfd2, pfdvalg);

	// print_valgrind(pfdvalg[0], 0, 100000, "valgrind start : \n");
	// for (int i = 0; tests[i]; i++)
	// 	test(pfd[1], pfd2[0], pfdvalg[0], tests[i], &p);
	// test(pfd[1], pfd2[0], pfdvalg[0], "exit", &p);
	// // si exit ne close pas ?
	// print_valgrind(pfdvalg[0], 0, 100000, "valgrind end : \n");
	// close(pfd[1]);
	// close(pfd2[0]);
	// close(pfdvalg[0]);
	// waitpid(pid, NULL, 0);

	return (0);
}
