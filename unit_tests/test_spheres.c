/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 04:07:08 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/28 04:12:36 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

int			main(int argc, char **argv)
{
	t_sphere	*sphere;
	t_conf		config;

	ft_bzero(&config, sizeof(t_conf));
	if (!(create_sphere(&config, *(argv + 1))))
	{
		printf("ERROR CREATING SPHERE\n");
		print_error();
		system("leaks a.out");
		return (1);
	}
	if ((sphere = get_sphere(&config, 100)))
	{
		printf("Shouldnt be printed bc error handling");
		print_error();
		free_spheres(&config);
		return (1);
	}
	sphere = get_sphere(&config, 0);
	if (g_errno)
	{
		print_error();
		free_spheres(&config);
		system("leaks a.out");
		return (1);
	}
	printf("SPHERE:\n");
	printf("LOC: X %f - Y %f - Z %f\n", sphere->loc.x, sphere->loc.y, sphere->loc.z);
	printf("DIAMETER: %f\n", sphere->diameter);
	printf("COLOR: #%.6X\n", sphere->color);
	printf("NEXT PTR: %p\n", sphere->next);
	return (0);
}
