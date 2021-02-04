/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 22:18:24 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/03 17:57:11 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/config.h"
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

t_camera	*create_camera(t_conf *conf, char *str)
{
	t_camera	cam;
	char		**tab;

	if (!(tab = ft_split(str, ' ')))
		return (NULL);
	if (ft_split_count(tab) != 4 || ft_strcmp(*tab, "c"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_FMT;
		return (NULL);
	}
	read_vec(cam.loc, *(tab + 1), 0.0f, 0.0f);
	read_vec(cam.dir, *(tab + 2), -1.0f, 1.0f);
	vec3_normalize(cam.dir, cam.dir);
	if ((cam.fov = read_val(*(tab + 3), 1)) < 0 || cam.fov > 180)
		g_errno = CONF_INV_NUM;
	cam.next = conf->c;
	conf->c = ft_memdup(&cam, sizeof(t_camera));
	ft_split_free(tab);
	return (conf->c);
}

t_camera	*get_camera(t_conf *conf, size_t index)
{
	size_t		count;
	t_camera	*ret;

	count = 1;
	ret = conf->c;
	while (count <= index && ret)
	{
		if (!(ret = ret->next))
			ret = conf->c;
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
