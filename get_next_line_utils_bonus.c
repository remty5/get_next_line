/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:09:59 by rvandepu          #+#    #+#             */
/*   Updated: 2023/11/08 02:52:21 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
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
