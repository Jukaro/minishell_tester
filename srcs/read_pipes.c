# include "../includes/tester.h"

int	print_valgrind_start(int valg_out)
{
	char	*valgrind;
	int		id;

	valgrind = NULL;
	while (!valgrind)
		valgrind = get_next_line(valg_out);
	ft_printf("valgrind start :\n");
	id = get_valgrind_id(valgrind);
	while (valgrind)
	{
		ft_printf("%s", valgrind);
		free(valgrind);
		valgrind = get_next_line(valg_out);
	}
	free(valgrind);
	return (id);
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
	usleep(1000);
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

char	*get_prompt(int fd, char *cmd, int msec)
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
	while ((!new_line || (new_line && !strstr(new_line, cmd))) && !timeout)
	{
		// if (!new_line)
		// 	printf("try : %s\n", new_line);
		// else
		// 	printf("try : %s", new_line);
		gettimeofday(&tv2, NULL);
		elapsed_time = (tv2.tv_sec - tv1.tv_sec) * 1000;
		elapsed_time += (tv2.tv_usec - tv1.tv_usec) / 1000;
		if (elapsed_time > msec)
			timeout = 1;
		new_line = get_next_line(fd);
		usleep(1000);
	}
	if (timeout)
		printf("prompt timeout :(\n");
	return (new_line);
}

static char	*get_first_line(int std_fd, int error_fd, int *fd, int msec)
{
	struct timeval tv1, tv2;
	double	elapsed_time;
	char	*std;
	char	*error;
	int		timeout;

	std = NULL;
	error = NULL;
	timeout = 0;
	gettimeofday(&tv1, NULL);
	while (!std && !error && !timeout)
	{
		gettimeofday(&tv2, NULL);
		elapsed_time = (tv2.tv_sec - tv1.tv_sec) * 1000;
		elapsed_time += (tv2.tv_usec - tv1.tv_usec) / 1000;
		if (elapsed_time > msec)
			timeout = 1;
		std = get_next_line(std_fd);
		error = get_next_line(error_fd);
		usleep(1000);
	}
	// printf("%f ms.\n", elapsed_time);
	if (std)
	{
		*fd = std_fd;
		return (std);
	}
	else if (error)
	{
		*fd = error_fd;
		return(error);
	}
	return (NULL);
}

void	get_answer(int std_fd, int error_fd, t_result *res, int mult_lines, int msec)
{
	char	*str;
	char	*tmp;
	char	*new_line;
	int		fd;
	double	elapsed_time;

	str = NULL;
	tmp = NULL;
	new_line = NULL;
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);
	new_line = get_first_line(std_fd, error_fd, &fd, msec);
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
	if (fd == std_fd)
		res->answer = str;
	else if (fd == error_fd)
		res->error = str;
	gettimeofday(&tv2, NULL);
	elapsed_time = (tv2.tv_sec - tv1.tv_sec) * 1000;
	elapsed_time += (tv2.tv_usec - tv1.tv_usec) / 1000;
	printf("Got answer in %f ms.\n", elapsed_time);
	return ;
}
