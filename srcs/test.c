/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 03:10:31 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/19 03:59:28 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <mlx.h>

int			main(int argc, char **argv)
{
	int			count;
	t_conf		config;
	void		*mlx_ptr;
	t_camera	*current;

	if (!(mlx_ptr = mlx_init()))
		return (-1);
	count = 0;
	while (++count < argc)
	{
		if (!(create_camera(&config, *(argv + count), mlx_ptr)) || g_errno)
		{
			if (g_errno)
				print_error();
			free_cameras(&config, mlx_ptr);
			return (-1);
		}
		current = get_camera(&config, count - 1);
		printf("IMG ADDR: %p\n", &current->img);
		printf("GRID ADDR:%p\n", &current->grid);
		printf("BPP: %d\n", current->bpp);
		printf("SLINE: %d\n", current->sline);
		printf("COORDS: %f - %f - %f\n", current->loc.x, current->loc.y, current->loc.z);
		printf("FACING: %f - %f - %f\n", current->dir.x, current->dir.y, current->dir.z);
		printf("FOV: %d\n", current->fov);
		printf("NEXT PTR: %p\n\n\n", &current->next);
	}
}
