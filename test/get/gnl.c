/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 03:18:32 by quesera           #+#    #+#             */
/*   Updated: 2023/06/27 21:21:22 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

t_list	*my_lst_make(t_list **head)
{
	(*head) = malloc(sizeof(t_list));
	if (!(*head))
		return (NULL);
	(*head)->fd = -1;
	(*head)->next = NULL;
	return (*head);
}

t_list	*my_lst_find(t_list **head, int f_fd)
{
	t_list	*temp;
	t_list	*remember;

	if (*head == NULL)
		*head = my_lst_make(head);
	temp = *head;
	while (temp)
	{
		if (temp->fd == f_fd)
			return (temp);
		temp = temp->next;
	}
	remember = *head;
	while ((*head)->next)
		(*head) = (*head)->next;
	temp = malloc(sizeof(t_list));
	if (!temp)
		return (NULL);
	(*head)->next = temp;
	temp->save = NULL;
	temp->next = NULL;
	temp->fd = f_fd;
	*head = remember;
	return (temp);
}

int	my_save_buf(t_list *find, char **ret, int check)
{
	char	*temp;
	int		idx;

	idx = BUFFER_SIZE + 1;
	while (idx--)
		find->buf[idx] = 0;
	check = 0;
	check = read(find->fd, find->buf, BUFFER_SIZE);
	find->save = my_strjoin(find->save, find->buf);
	idx = -1;
	while (find->save[++idx])
	{
		if (find->save[idx] == '\n')
		{
			*ret = my_substr(find->save, 0, idx + 1);
			temp = my_substr(find->save, idx + 1, \
							my_strlen(find->save) - (idx + 1));
			free(find->save);
			find->save = temp;
			return (1);
		}
	}
	return (check);
}

char	*my_save_check(int fd, t_list **head)
{
	char		*ret;
	int			check;
	t_list		*find;

	ret = 0;
	check = 0;
	find = my_lst_find(head, fd);
	while (ret == 0)
	{
		check = my_save_buf(find, &ret, check);
		if (check < 0 || (check == 0 && find->save == 0))
		{
			my_lst_free(find, *head);
			return (NULL);
		}
		else if (check == 0 && find->save != 0)
		{
			ret = my_substr(find->save, 0, my_strlen(find->save));
			my_lst_free(find, *head);
			return (ret);
		}
	}
	return (ret);
}

int	get_next_line(int fd, char **ret)
{
	static t_list	*head;
	t_list			*find;
	// char			*ret;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		find = head;
		while (find)
		{
			if (find->fd == fd)
			{
				my_lst_free(find, head);
				return (false);
			}
			find = find->next;
		}
		return (false);
	}
	*ret = my_save_check(fd, &head);
	if (head->fd == -1 && head->next == NULL)
	{
		free(head);
		head = NULL;
	}
	if (*ret == NULL)
		return (false);
	return (true);
}