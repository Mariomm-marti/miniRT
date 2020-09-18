/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:58:11 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/18 20:29:32 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <get_next_line.h>
#include "../includes/minirt.h"

t_errcode		read_res(t_conf *conf, char const *line)
{
	if (!ft_isspace(*line))
		return (CONF_INV_FMT);
	while (ft_isspace(*line))
		line++;
	if (!ft_isdigit(*line))
		return (CONF_INV_RES);
	conf->res.x = *line - '0';
	while (ft_isdigit(*(line + 1)))
		conf->res.x = conf->res.x * 10 + (*++line - '0');
	if (!ft_isspace(*++line))
		return (CONF_INV_RES);
	while (ft_isspace(*line))
		line++;
	if (!ft_isdigit(*line))
		return (CONF_INV_RES);
	conf->res.y = *line - '0';
	while (ft_isdigit(*(line + 1)))
		conf->res.y = conf->res.y * 10 + (*++line - '0');
	if (conf->res.x > SCREEN_WIDTH)
		conf->res.x = SCREEN_WIDTH;
	if (conf->res.y > SCREEN_HEIGHT)
		conf->res.y = SCREEN_HEIGHT;
	return (*++line ? CONF_INV_RES : 0);
}

t_errcode		read_conf(t_conf *conf, char const *path)
{
	int const	fd = open(path, O_RDONLY);
	char		*line;
	t_errcode	err;

	if (fd < 0)
		return (CONF_MISSING);
	while (get_next_line(fd, &line) == 1)
	{
		if (*line == 'R')
			err = read_res(conf, line + 1);
		free(line);
	}
	if (line)
		free(line);
	return (err = close(fd) < 0 ? CONF_MISSING : err);
}
