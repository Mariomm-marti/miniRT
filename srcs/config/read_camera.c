/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 22:18:24 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/16 22:37:01 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stddef.h>

int		create_camera(t_conf *conf, char const *str, void *mlx_ptr)
{
	t_camera	cam;
	int			count;
	char		**tab;

	if (*str != 'c')
		return (0);
	if (!(tab = ft_split(&count, str, ' ')) || count != 4)
	{
		g_errno = CONF_INV_CAM;
		return (0);
	}
	cam.img = mlx_new_image(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	cam.grid = (int *)mlx_get_data_addr(cam.img, &cam.bpp, &cam.sline, &count);
	cam.coords = read_vec(*(tab + 1), 0.0f, 0.0f, 0);
	cam.facing = read_vec(*(tab + 2), 0.0f, 1.0f, 0);
	cam.fov = read_val(*(tab + 3), 0.0f, 180.0f, 1);
	ft_split_free(tab);
	// TODO insert cam
	return (1);
}
