/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:28:01 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/01 18:17:07 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

/*
**	DESCRIPTION
**		Initialize buffer to 0, reads file for _BUFFER_SIZE_ and joins previous
**		and current read
**	RETURN VALUES
**		Returns -1 if failed to read, 0 if no bytes could be read, and
**		otherwise the number of bytes read
*/

static int	read_next_buff(int fd, char **tab)
{
	char	*tmp;
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;

	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes < 0)
		return (-1);
	if (read_bytes == 0)
		return (0);
	buffer[read_bytes] = 0;
	tmp = gnl_strjoin(tab[fd], buffer);
	if (tab[fd])
		free(tab[fd]);
	tab[fd] = tmp;
	return (read_bytes);
}

/*
**	DESCRIPTION
**		Updates line contents with the different options of read, they can be:
**		- File is invalid (read bytes are less than 0), returns -1
**		- File exists, but it's empty (read bytes are 0), returns 0
**		- A NL was found, so line takes the value prior to NL and returns 1
**		- No NL was found and its EOF, if that happens line is set to the whole
**			previous read buffer and the whole memory is free
**	RETURN VALUES
**		The return value is passed to get_next_line, so it has the same return
**		options
*/

static int	update_line(int fd, int read, char **tab, char **line)
{
	char *x;

	if (read < 0)
		return (-1);
	if (!tab[fd] && read == 0)
	{
		*line = gnl_strdup("");
		return (0);
	}
	if (gnl_strchr(tab[fd], '\n') != -1)
	{
		*line = gnl_substr(tab[fd], 0, gnl_strchr(tab[fd], '\n'));
		x = gnl_substr(tab[fd],
				gnl_strchr(tab[fd], '\n') + 1, gnl_strlen(tab[fd]));
		free(tab[fd]);
		tab[fd] = x;
		return (1);
	}
	*line = gnl_strdup(tab[fd]);
	free(tab[fd]);
	tab[fd] = NULL;
	return (0);
}

/*
**	DESCRIPTION
**		General part of the get_next_line, sanitize input, checks for
**		existing NL in previous reads, and finally read until NL is
**		found or file reach EOF
**	RETURN VALUES
**		- If any problem, -1
**		- If a NL was found, 1
**		- When EOF, 0
*/

int			get_next_line(int fd, char **line)
{
	static char		*tab[4096];
	int				read_bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (tab[fd] && gnl_strchr(tab[fd], '\n') != -1)
		return (update_line(fd, 0, tab, line));
	while ((read_bytes = read_next_buff(fd, tab)) > 0 &&
			gnl_strchr(tab[fd], '\n') == -1)
		;
	return (update_line(fd, read_bytes, tab, line));
}
