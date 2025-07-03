/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:33:06 by patrik            #+#    #+#             */
/*   Updated: 2025/07/03 23:35:46 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int		get_newline_index(t_buffer *buffer);
char	*extract_line(char *buff, char **next_line, int s_buff, int pos);
int		read_next(int file_descriptor, t_buffer *b, char **new_line);

void	handle_line_extraction(t_buffer buffer, char **line_out,
		int newline_index)
{
	buffer.data = extract_line(buffer.data, line_out, buffer.size,
			newline_index);
	buffer.size = buffer.size - (newline_index + 1);
}

char	*get_next_line(int file_descriptor)
{
	char			*new_line;
	int				newline_position;
	static t_buffer	buffer = {0, NULL};

	if (BUFFER_SIZE <= 0)
		return (NULL);
	newline_position = -666;
	while (1)
	{
		newline_position = get_newline_index(&buffer);
		new_line = NULL;
		if (newline_position >= 0)
		{
			handle_line_extraction(buffer, &new_line, newline_position);
			break ;
		}
		if (!read_next(file_descriptor, &buffer, &new_line))
			break ;
	}
	return (new_line);
}
