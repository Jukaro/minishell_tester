#include "../includes/tester.h"

int		get_method(char *str)
{
	if (!ft_strncmp("cmp", str, 3))
		return (CMP);
	else if (!ft_strncmp("find", str, 4))
		return (FIND);
	return (-1);
}

char	*ft_strchrset(char *str, char *set)
{
	for (int i = 0; str[i]; i++)
		for (int j = 0; set[j]; j++)
			if (str[i] == set[j])
				return (&str[i]);
	return (NULL);
}

int		is_in_set(char c, char *charset)
{
	for (int i = 0; charset[i]; i++)
		if (charset[i] == c)
			return (1);
	return (0);
}

int		skip_quotes(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote)
	{
		if (str[i] == '\\')
			i++;
		if (str[i])
			i++;
	}
	return (i);
}

char	*get_result(char *str)
{
	int		i;
	int		j;
	int		eoq;
	int		quotes_count;
	int		backslash_count;
	char	*res;
	char	*final_res;

	i = 0;
	for ( ; str[i] && !is_in_set(str[i], " \t\n"); i++)
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += skip_quotes(&str[i], str[i]);
	}
	res = ft_substr(str, 0, i);
	i = 0;
	quotes_count = 0;
	for ( ; res[i]; i++)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i += skip_quotes(&str[i], str[i]);
			quotes_count += 2;
		}
	}
	i = 0;
	backslash_count = 0;
	for ( ; res[i]; i++)
	{
		if (str[i] == '\\')
		{
			backslash_count++;
			i++;
		}
	}
	final_res = ft_calloc(ft_strlen(res) - backslash_count - quotes_count + 1, sizeof(char));
	i = 0;
	j = 0;
	while (res[i])
	{
		if (res[i] == '\'' || res[i] == '\"')
		{
			eoq = skip_quotes(&res[i], res[i]);
			eoq = i + eoq;
			i++;
			while (i < eoq)
			{
				if (res[i] == '\\')
					i++;
				final_res[j] = res[i];
				if (res[i])
					i++;
				j++;
			}
			if (res[i])
				i++;
		}
		if (res[i] != '\'' && res[i] != '\"')
			final_res[j] = res[i];
		if (res[i])
			i++;
		j++;
	}
	free(res);
	return (final_res);
}

int	get_signal(char *str)
{
	char	*sig;

	sig = get_result(str);
	if (!strcmp("CTRL C", sig))
		return (SIGINT);
	else if (!strcmp("CTRL \\", sig))
		return (SIGQUIT);
	else if (!strcmp("CTRL D", sig))
		return (EOF);
	return (0);
}
