/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_planes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:13:04 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/28 14:19:27 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>
#include <stdlib.h>

int			main(int argc, char **argv)
{
	t_plane		*plane;
	t_conf		config;

	ft_bzero(&config, sizeof(t_conf));
	if (!(create_plane(&config, *(argv + 1))))
	{
		printf("ERROR CREATING PLANE");
		print_error();
		system("leaks a.out");
		return (1);
	}
	if ((plane = get_plane(&config, 100)))
	{
		printf("Shouldnt be printed bc error handling");
		print_error();
		free_planes(&config);
		system("leaks a.out");
		return (1);
	}
	plane = get_plane(&config, 0);
	if (g_errno)
	{
		print_error();
		free_planes(&config);
		system("leaks a.out");
		return (1);
	}
	printf("PLANE:\n");
	printf("LOC  : X %f - Y %f - Z %f\n", plane->loc.x, plane->loc.y, plane->loc.z);
	printf("DIR  : X %f - Y %f - Z %f\n", plane->dir.x, plane->dir.y, plane->dir.z);
	printf("COLOR: #%.6X\n", plane->color);
	printf("NEXT : %p\n", plane->next);
	free_planes(&config);
	system("leaks a.out");
	return (0);
}
