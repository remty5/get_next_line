/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:09:29 by rvandepu          #+#    #+#             */
/*   Updated: 2023/11/08 01:43:21 by rvandepu         ###   ########.fr       */
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

	//ft_printmem(mem);
	n = 0;
	while (mem)
	{
		if (!mem->read)
			return (n);
		i = -1;
		while (++i < mem->read)
			if (mem->content[i] == '\n')
				return (n + i + 1);
		n += mem->read;
		mem = mem->next;
	}
	return (0);
}

bool	ft_get_line(t_buf **mem, char **line)
{
	int	l;
	int	c;

	l = ft_mem_has_line(*mem);
	c = l;
	//printf("[get_line] l: %d\n", l);
	//ft_printmem(*mem);
	*line = malloc(l + 1);
	if (*line == NULL)
		return (!ft_memclear(mem));
	// while remaining?
	while (*mem)
	{
		//printf("[get_line] c:%p,n:%p,data:'%.*s',r:%d\n", *mem, (*mem)->next,
		//	(*mem)->read, (*mem)->content, ft_mem_has_line(*mem));
		ft_memcpy(*line + l - c, (*mem)->content,
			(*mem)->read * ((*mem)->read <= c) + c * ((*mem)->read > c));
		c -= (*mem)->read;
		mem = &(*mem)->next;
	}
	(*line)[l] = '\0';
	//printf("[get_line] result: '%s'\n", *line);
	return (true);
}

// TODO: rewrite this abomination
bool	ft_mem_next(t_buf **mem)
{
	t_buf	*new;
	t_buf	*buf;
	int		left;

	//ft_printmem(*mem);
	buf = *mem;
	left = ft_mem_has_line(buf);
	while (buf && buf->read <= left)
	{
		//printf("[mem_next] buf %p '%.*s' %d to %p\n", buf, buf->read,
		//	buf->content, buf->read, buf->next);
		left -= buf->read;
		buf = buf->next;
	}
	if (!buf)
		return (ft_memclear(mem));
	new = malloc(sizeof(t_buf));
	if (new == NULL)
		return (!ft_memclear(mem));
	new->next = NULL;
	//printf("[mem_next] last buf: %p, r: %d, data: '%.*s'\n", buf, buf->read,
	//	buf->read, buf->content);
	//printf("[mem_next] remaining: %d\n", ft_mem_has_line(buf));
	new->read = buf->read - ft_mem_has_line(buf);
	ft_memcpy(new->content, buf->content + ft_mem_has_line(buf), new->read);
	ft_memclear(mem);
	*mem = new;
	return (true);
}

char	*get_next_line(int fd)
{
	static t_buf	*mem = NULL;
	char			*line;

	if (fd < 0)
		return (NULL);
	//printf("[GNL] reading\n");
	while (!ft_mem_has_line(mem))
		if (!ft_read_to_mem(&mem, fd))
			return (NULL);
	//printf("[GNL] copying line\n");
	if (!ft_get_line(&mem, &line))
		return (NULL);
	//printf("[GNL] cleaning mem: %p\n", mem);
	if (!ft_mem_next(&mem))
	{
		free(line);
		return (NULL);
	}
	//printf("[GNL] returning, showing mem: %p\n", mem);
	//ft_printmem(mem);
	return (line);
}
