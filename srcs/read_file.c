/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:58:11 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/21 20:47:31 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <get_next_line.h>
#include "../includes/minirt.h"

t_errcode		read_color(t_color *out, char const *line, t_byte len)
{
	t_color		current_color;

	if (len >= 3 || !ft_isdigit(*line) || (current_color = *line - '0') < 0)
		return (CONF_INV_RGB);
	while (ft_isdigit(*(line + 1)))
		current_color = current_color * 10 + (*++line - '0');
	if (current_color > 255)
		return (CONF_INV_RGB);
	*out = (*out << (8 * !!len)) | current_color;
	if (*++line == ',')
		return (read_color(out, line + 1, len + 1));
	return (len != 2 ? CONF_INV_RGB : 0);
}

t_errcode		read_rnumber(float *out, char const *line, float min, float max)
{
	int		integer;

	*out = *line == '-' ?  -0.0f : 0.0f;
	if (!ft_isdigit(*++line))
		return (CONF_INV_NUM);
	return (*out < min || *out > max ? CONF_INV_NUM : 0);
}

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
	conf->res.x > SCREEN_WIDTH ? conf->res.x = SCREEN_WIDTH : 0;
	if (!ft_isspace(*++line))
		return (CONF_INV_RES);
	while (ft_isspace(*line))
		line++;
	if (!ft_isdigit(*line))
		return (CONF_INV_RES);
	conf->res.y = *line - '0';
	while (ft_isdigit(*(line + 1)))
		conf->res.y = conf->res.y * 10 + (*++line - '0');
	conf->res.y > SCREEN_HEIGHT ? conf->res.y = SCREEN_HEIGHT : 0;
	return (*++line ? CONF_INV_RES : 0);
}

t_errcode		read_amb(t_conf *conf, char const *line)
{
	t_errcode	error;

	if (!ft_isspace(*line))
		return (CONF_INV_FMT);
	while (ft_isspace(*line))
		line++;
	error = read_rnumber(&conf->amb.ratio, line, 0.0f, 1.0f);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	if (!ft_isspace(*line))
		return (CONF_INV_FMT);
	while (ft_isspace(*line))
		line++;
	return (!error ? read_color(&conf->amb.color, line, 0) : error);
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
