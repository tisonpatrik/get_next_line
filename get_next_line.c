/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:33:06 by patrik            #+#    #+#             */
/*   Updated: 2025/07/03 22:12:36 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "get_next_line.h"

int		has_next_line(t_buffer *buffer);
char	*extract_line(char *buff, char **next_line, int s_buff, int pos);
char	*concat(char *buff, char *addme, size_t s_buff, size_t s_addme);
int		read_next(int file_descriptor, t_buffer *b, char **new_line);

static t_buffer	s_buffer = {0, NULL};

char	*get_next_line(int file_descriptor)
{
	char			*new_line;
	int				newline_position;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	newline_position = -1;
	while (1)
	{
		newline_position = has_next_line(&s_buffer);
		new_line = NULL;
		if (newline_position >= 0)
		{
			s_buffer.buffer_data = extract_line(
					s_buffer.buffer_data, &new_line,
					s_buffer.buffer_size,
					newline_position);
			s_buffer.buffer_size = s_buffer.buffer_size
				- (newline_position + 1);
			break ;
		}
		if (!read_next(file_descriptor, &s_buffer,
				&new_line))
			break ;
	}
	return (new_line);
}
