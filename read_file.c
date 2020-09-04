/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:40:10 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/04 14:12:54 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <fctntl.h>

float		readv(char *line)
{
	
}

t_errcode	read_file(t_conf *conf, char const *path)
{
	int const	fd = open(path, O_RDONLY);
	char		*line; 

	if (fd < 0)
		return (CONF_MISSING);
	while (get_next_line(fd, &line) == 1)
	{
		// TODO Today: read each val
		free(line);
	}
	if (line)
		free(line);
	return (close(fd) ? CONF_MISSING : 0);
}
