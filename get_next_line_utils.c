/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:09:59 by rvandepu          #+#    #+#             */
/*   Updated: 2023/11/08 00:38:28 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	//printf("[memcpy] to: %p, from: %p, size: %lu\n", dest, src, n);
	while (n-- && (src || dest))
		((char *) dest)[n] = ((char *) src)[n];
	return (dest);
}

// TODO remove
void	ft_printmem(t_buf *mem)
{
	while (mem)
	{
		printf("[MEM] read: %d, content: '%.*s'\n", mem->read, mem->read,
			mem->content);
		mem = mem->next;
	}
}

bool	ft_memclear(t_buf **mem)
{
	t_buf	*next;

	while (*mem)
	{
		next = (*mem)->next;
		free(*mem);
		*mem = next;
	}
	return (true);
}
