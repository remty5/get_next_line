/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:09:59 by rvandepu          #+#    #+#             */
/*   Updated: 2023/11/07 10:06:33 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	printf("[memcpy] to: %p, from: %p, size: %lu\n", dest, src, n);
	while (n-- && (src || dest))
		((char *) dest)[n] = ((char *) src)[n];
	return (dest);
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
