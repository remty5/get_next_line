/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:09:29 by rvandepu          #+#    #+#             */
/*   Updated: 2023/11/07 10:35:13 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	ft_read_to_mem(t_buf **mem, int fd)
{
	t_buf	*buf;

	buf = malloc(sizeof(t_buf));
	if (buf == NULL)
		return (!ft_memclear(mem));
	buf->next = NULL;
	buf->read = read(fd, buf->content, BUFFER_SIZE);
	if (buf->read < 0 || (*mem == NULL && buf->read == 0))
	{
		free(buf);
		return (!ft_memclear(mem));
	}
	while (*mem)
		mem = &(*mem)->next;
	(*mem) = buf;
	return (true);
}

int	ft_mem_has_line(t_buf *mem)
{
	int	i;
	int	n;

	n = 0;
	while (mem)
	{
		if (!mem->read)
			return (n);
		i = -1;
		while (++i < mem->read)
			if (mem->content[i] == '\n')
				return (n + i);
		n += mem->read;
		mem = mem->next;
	}
	return (0);
}

bool	ft_get_line(t_buf **mem, char **line)
{
	int	l;

	l = ft_mem_has_line(*mem);
	*line = malloc(l + 1);
	if (*line == NULL)
		return (!ft_memclear(mem));
	while (*mem)
	{
		ft_memcpy(*line + l - ft_mem_has_line(*mem), (*mem)->content, \
			(*mem)->read * ((*mem)->read <= ft_mem_has_line(*mem)) + (1 + \
			ft_mem_has_line(*mem)) * ((*mem)->read > ft_mem_has_line(*mem)));
		mem = &(*mem)->next;
	}
	(*line)[l] = '\0';
	return (true);
}

// TODO: rewrite this abomination
/*#include <stdio.h>

bool	ft_mem_next(t_buf **mem)
{
	t_buf	*new;
	t_buf	*buf;

	new = malloc(sizeof(t_buf));
	if (new == NULL)
		return (!ft_memclear(mem));
	new->next = NULL;
	buf = *mem;
	while (buf && buf->read <= ft_mem_has_line(buf))
	{
		buf->content[buf->read] = '\0';
		printf("[mem_next] buf %p %s %d to %p\n", buf, buf->content, buf->read, buf->next);
		buf = buf->next;
	}
	new->read = buf->read - ft_mem_has_line(buf) - 1;
	ft_memcpy(new->content, buf->content + ft_mem_has_line(buf) + 1, new->read);
	ft_memclear(mem);
	*mem = new;
	return (true);
}*/

char	*get_next_line(int fd)
{
	static t_buf	*mem = NULL;
	char			*line;

	if (fd < 0)
		return (NULL);
	while (!ft_mem_has_line(mem))
		if (!ft_read_to_mem(&mem, fd))
			return (NULL);
	if (!ft_get_line(&mem, &line))
		return (NULL);
	if (!ft_mem_next(&mem))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
