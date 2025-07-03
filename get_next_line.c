/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:33:06 by patrik            #+#    #+#             */
/*   Updated: 2025/07/03 20:38:47 by patrik           ###   ########.fr       */
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

// Global buffer array definition
// Stores buffered data for each file descriptor (up to MAX_FD)
// Each file descriptor gets its own buffer to maintain state between calls
t_buffer	g_file_buffers[MAX_FD] = {0};

char	*get_next_line(int file_descriptor)
{
	char			*new_line;
	int				newline_position;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	newline_position = -1;
	while (1)
	{
		newline_position = has_next_line(&g_file_buffers[file_descriptor]);
		new_line = NULL;
		if (newline_position >= 0)
		{
			g_file_buffers[file_descriptor].buffer_data = extract_line(
					g_file_buffers[file_descriptor].buffer_data, &new_line,
					g_file_buffers[file_descriptor].buffer_size,
					newline_position);
			g_file_buffers[file_descriptor].buffer_size -= newline_position + 1;
			break ;
		}
		if (!read_next(file_descriptor, &g_file_buffers[file_descriptor],
				&new_line))
			break ;
	}
	return (new_line);
}
