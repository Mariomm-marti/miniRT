/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 22:27:34 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/30 22:52:02 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/config.h"
#include "../../includes/minirt.h"
#include <fcntl.h>
#include <unistd.h>

static int	setup_line(t_conf *conf, char *str, void *mlx_ptr)
{
	// TODO
	return (0);
}

int			read_config(t_conf *conf, char *path, void *mlx_ptr)
{
	int			fd;
	char		*line;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (g_errno = CONF_MISSING);
	while (get_next_line(fd & 2047, &line) == 1)
	{
		// TODO
		free(line);
	}
	if (line)
		free(line);
	return (close(fd));
}
