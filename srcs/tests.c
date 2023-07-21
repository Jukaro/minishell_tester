#include "../includes/tester.h"

t_test	*ft_testnew(void)
{
	t_test	*new_elem;

	new_elem = malloc(sizeof(t_test));
	if (new_elem == NULL)
		return (NULL);
	new_elem->next = NULL;
	return (new_elem);
}

void	ft_testadd_back(t_test **lst, t_test *new)
{
	t_test	*last_elem;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_elem = *lst;
	while (last_elem->next != NULL)
		last_elem = last_elem->next;
	last_elem->next = new;
}

void	ft_testclear(t_test **lst)
{
	t_test	*ptr;
	t_test	*before_elem;

	if (lst == NULL)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		free(ptr->cmd);
		if (ptr->result)
			free(ptr->result);
		before_elem = ptr;
		ptr = ptr->next;
		free(before_elem);
	}
	*lst = NULL;
}

int	ft_testsize(t_test *lst)
{
	int		list_size;
	t_test	*ptr;

	list_size = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		list_size++;
	}
	return (list_size);
}