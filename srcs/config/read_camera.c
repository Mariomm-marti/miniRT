/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 22:18:24 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/21 22:20:38 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

int			create_camera(t_conf *conf, char *str, void *mlx_ptr)
{
	t_camera	*head;
	t_camera	cam;
	char		**tab;
	int			count;

	if (*str != 'c')
		return (0);
	if (!(tab = ft_split(&count, str, ' ')))
		return (!(g_errno = CONF_INV_CAM));
	if (count != 4)
		return (!(ft_split_free(tab)));
	cam.img = mlx_new_image(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	cam.grid = (int *)mlx_get_data_addr(cam.img, &cam.bpp, &cam.sline, &count);
	cam.loc = read_vec(*(tab + 1), 0.0f, 0.0f, 0);
	cam.dir = read_vec(*(tab + 2), 0.0f, 1.0f, 0);
	cam.fov = read_val(*(tab + 3), 0.0f, 180.0f, 1);
	cam.next = NULL;
	ft_split_free(tab);
	if (!(head = conf->c))
		return (!!(conf->c = ft_memdup(&cam, sizeof(t_camera))));
	while (head->next)
		head = head->next;
	head->next = ft_memdup(&cam, sizeof(t_camera));
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

	if (!conf->c)
		return ;
	while (conf->c)
	{
		copy = conf->c->next;
		mlx_destroy_image(mlx_ptr, conf->c->img);
		free(conf->c);
		conf->c = copy;
	}
}
