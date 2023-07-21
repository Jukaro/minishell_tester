#include "../includes/tester.h"

static void	setup_pipes(int request[2], int child_out[2], int child_error[2], int valgrind[2])
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

void	start_minishell(char **cmd_line, char **envp, pid_t *pid, int request[2], int child_out[2], int child_error[2], int valgrind[2])
{
	setup_pipes(request, child_out, child_error, valgrind);
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
