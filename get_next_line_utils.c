/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:31:58 by ptison            #+#    #+#             */
/*   Updated: 2025/07/03 22:10:23 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	has_next_line(t_buffer *buffer)
{
	int	pos;

	pos = 0;
	while (pos < buffer->buffer_size)
		if (buffer->buffer_data[pos++] == '\n')
			return (pos - 1);
	return (-1);
}

char	*update_buffer(char *buff, int s_buff, int pos)
{
	char	*newbuff;
	int		it1;
	int		it2;

	it1 = 0;
	it2 = pos + 1;
	newbuff = malloc(s_buff - pos - 1);
	if (!newbuff)
		return (NULL);
	while (it2 < s_buff)
		newbuff[it1++] = buff[it2++];
	free(buff);
	return (newbuff);
}

char	*extract_line(char *buff, char **next_line, int s_buff, int pos)
{
	int		i;
	char	*newbuff;

	i = 0;
	if (!buff || !next_line || pos >= s_buff)
		return (NULL);
	*next_line = malloc(pos + 2);
	if (!(*next_line))
		return (NULL);
	while (i <= pos)
	{
		(*next_line)[i] = buff[i];
		i++;
	}
	(*next_line)[i] = '\0';
	if (s_buff - pos - 1 <= 0)
	{
		free(buff);
		return (NULL);
	}
	newbuff = update_buffer(buff, s_buff, pos);
	if (!newbuff)
		free(*next_line);
	return (newbuff);
}

char	*concat(char *buff, char *addme, size_t s_buff, size_t s_addme)
{
	char	*newbuff;	
	int		offset;

	offset = s_buff;
	newbuff = malloc(s_buff + s_addme);
	if (!newbuff)
		return (NULL);
	while (s_buff--)
		newbuff[s_buff] = buff[s_buff];
	while (s_addme--)
		newbuff[offset + s_addme] = addme[s_addme];
	free(buff);
	return (newbuff);
}

int	read_next(int file_descriptor, t_buffer *b, char **new_line)
{
	char	*tmp;
	int		bytes_read;

	tmp = malloc(BUFFER_SIZE);
	bytes_read = read(file_descriptor, tmp, BUFFER_SIZE);
	if (bytes_read < 0 || (bytes_read == 0 && b->buffer_size == 0) || !tmp)
	{
		b->buffer_size = 0;
		free(tmp);
		return (0);
	}
	else if (bytes_read == 0)
	{
		b->buffer_data = extract_line(b->buffer_data, new_line, b->buffer_size,
				b->buffer_size - 1);
		b->buffer_size = 0;
		free(tmp);
		return (0);
	}
	b->buffer_data = concat(b->buffer_data, tmp, b->buffer_size, bytes_read);
	b->buffer_size = b->buffer_size + bytes_read;
	free(tmp);
	return (1);
}
