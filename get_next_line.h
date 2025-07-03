/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:32:06 by ptison            #+#    #+#             */
/*   Updated: 2025/07/03 20:38:45 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif

typedef struct s_buffer
{
	int		buffer_size;
	char	*buffer_data;
}	t_buffer;

// Global buffer array for managing multiple file descriptors
extern t_buffer	g_file_buffers[MAX_FD];

char	*get_next_line(const int file_descriptor);
#endif