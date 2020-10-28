/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cameras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 22:50:52 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/28 02:35:38 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

int			main(int argc, char **argv)
{
	t_camera	*cam;
	t_conf		config;
	void		*mlx_ptr;

	if (!(mlx_ptr = mlx_init()))
		return (1);
	ft_bzero(&config, sizeof(t_conf));
	if (!(create_camera(&config, *(argv + 1), mlx_ptr)))
	{
		printf("ERROR CREATING CAMERA\n");
		print_error();
		system("leaks a.out");
		return (1);
	}
	if ((cam = get_camera(&config, 100)))
	{
		printf("Shouldnt be printed bc error handling");
		print_error();
		free_cameras(&config, mlx_ptr);
		return (1);
	}
	cam = get_camera(&config, 0);
	if (g_errno)
	{
		print_error();
		free_cameras(&config, mlx_ptr);
		system("leaks a.out");
		return (1);
	}
	printf("CAM:\n");
	printf("IMG PTR: %p\n", cam->img);
	printf("GRID PTR: %p\n", cam->grid);
	printf("BPP: %d\n", cam->bpp);
	printf("SLINE: %d\n", cam->sline);
	printf("LOC X: %f - Y: %f - Z: %f\n", cam->loc.x, cam->loc.y, cam->loc.z);
	printf("DIR X: %f - Y: %f - Z: %f\n", cam->dir.x, cam->dir.y, cam->dir.z);
	printf("FOV: %d\n", cam->fov);
	printf("NEXT PTR: %p\n", cam->next);
	free_cameras(&config, mlx_ptr);
	system("leaks a.out");
}
