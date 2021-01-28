/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 22:27:34 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/27 18:07:22 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/config.h"
#include "../../includes/minirt.h"
#include <get_next_line.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <mlx.h>

static t_res	get_resolution(char *str, t_byte *code)
{
	t_res	res;
	char	**tab;

	if ((*code & 1) || !(tab = ft_split(str, ' ')))
	{
		g_errno = CONF_DUPPED_PARAM;
		return ((t_res){0, 0});
	}
	if (ft_split_count(tab) != 3 || ft_strcmp(*tab, "R"))
	{
		ft_split_free(tab);
		*code = *code | 1;
		g_errno = CONF_INV_RES;
		return ((t_res){0, 0});
	}
	if ((res.x = read_val(*(tab + 1), 1)) < 960 || res.x > SCREEN_WIDTH)
		res.x = SCREEN_WIDTH;
	if ((res.y = read_val(*(tab + 2), 1)) < 540 || res.y > SCREEN_HEIGHT)
		res.y = SCREEN_HEIGHT;
	ft_split_free(tab);
	*code = *code | 1;
	return (res);
}

static t_amb	get_ambient(char *str, t_byte *code)
{
	t_amb	amb;
	char	**tab;

	if ((*code & 2) || !(tab = ft_split(str, ' ')))
	{
		g_errno = CONF_DUPPED_PARAM;
		return ((t_amb){0.0, 0});
	}
	if (ft_split_count(tab) != 3 || ft_strcmp(*tab, "A"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_AMB;
		*code = *code | 2;
		return ((t_amb){0.0, 0});
	}
	if ((amb.ratio = read_val(*(tab + 1), 0)) < 0.0f || amb.ratio > 1.0f)
		g_errno = CONF_INV_AMB;
	amb.color = read_color(*(tab + 2));
	ft_split_free(tab);
	*code = *code | 2;
	return (amb);
}

static int		setup_line(t_conf *conf, t_byte *code, char *str)
{
	if (*str == 'R')
		conf->r = get_resolution(str, code);
	else if (*str == 'A')
		conf->a = get_ambient(str, code);
	else if (*str == 'c' && *(str + 1) != 'y')
		create_camera(conf, str);
	else if (*str == 'l')
		create_light(conf, str);
	else if (*str == 's' && *(str + 1) == 'p')
		create_sphere(conf, str);
	else if (*str == 'p')
		create_plane(conf, str);
	else if (*str == 's' && *(str + 1) == 'q')
		create_square(conf, str);
	else if (*str == 'c' && *(str + 1) == 'y')
		create_cylinder(conf, str);
	else if (*str == 't')
		create_triangle(conf, str);
	else if (*str)
		return (0);
	return (1);
}

static void		setup_images(t_conf *conf, void *mlx_ptr)
{
	t_camera	*cur;
	int			end;

	if (!conf->c)
		create_camera(conf, "c 0,0,0 0,0,1 80");
	cur = conf->c;
	while (cur)
	{
		cur->img = mlx_new_image(mlx_ptr, conf->r.x, conf->r.y);
		cur->grid = mlx_get_data_addr(cur->img, &cur->bpp, &cur->sline, &end);
		cur = cur->next;
	}
}

int				read_config(t_conf *conf, char *path, void *mlx_ptr)
{
	t_byte		code;
	int			fd;
	char		*line;

	if ((fd = open(path, O_RDONLY)) < 0)
	{
		g_errno = CONF_MISSING;
		return (0);
	}
	code = 0;
	while (!g_errno && get_next_line(fd, &line) == 1)
	{
		if (!setup_line(conf, &code, line))
			g_errno = CONF_INV_FMT;
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	setup_images(conf, mlx_ptr);
	if (code != 3 && !g_errno)
		g_errno = CONF_MISSING_PARAM;
	return (!close(fd));
}
