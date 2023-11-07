/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:10:02 by rvandepu          #+#    #+#             */
/*   Updated: 2023/11/07 09:25:30 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buf {
	char			content[BUFFER_SIZE];
	int				read;
	struct s_buf	*next;
}	t_buf;

// get_next_line.c
bool	ft_read_to_mem(t_buf **mem, int fd);
int		ft_mem_has_line(t_buf *mem);
bool	ft_get_line(t_buf **mem, char **line);
bool	ft_mem_next(t_buf **mem);
char	*get_next_line(int fd);

// get_next_line_utils.c
void	*ft_memcpy(void *dest, const void *src, size_t n);
bool	ft_memclear(t_buf **mem);

#endif
