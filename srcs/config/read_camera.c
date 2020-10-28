/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 22:18:24 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/28 02:35:53 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

int			create_camera(t_conf *conf, char *str, void *mlx_ptr)
{
	t_camera	cam;
	char		**tab;
	int			endian;

	if (!(tab = ft_split(str, ' ')))
		return (0);
	if (ft_split_count(tab) != 4 || ft_strcmp(*tab, "c"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_FMT;
		return (0);
	}
	cam.img = mlx_new_image(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	cam.grid = (int *)mlx_get_data_addr(cam.img, &cam.bpp, &cam.sline, &endian);
	cam.loc = read_vec(*(tab + 1), 0.0f, 0.0f);
	cam.dir = read_vec(*(tab + 2), 0.0f, 1.0f);
	if ((cam.fov = read_val(*(tab + 3), 1)) < 0 || cam.fov > 180)
		g_errno = CONF_INV_NUM;
	cam.next = conf->c;
	conf->c = ft_memdup(&cam, sizeof(t_camera));
	ft_split_free(tab);
	return (1);
}

t_camera	*get_camera(t_conf *conf, size_t index)
{
	size_t		count;
	t_camera	*ret;

	count = 1;
	ret = conf->c;
	while (count <= index && ret)
	{
		ret = ret->next;
		count++;
	}
	return (ret);
}

void		free_cameras(t_conf *conf, void *mlx_ptr)
{
	t_camera	*copy;

	while (conf->c)
	{
		copy = conf->c->next;
		mlx_destroy_image(mlx_ptr, conf->c->img);
		free(conf->c);
		conf->c = copy;
	}
}
