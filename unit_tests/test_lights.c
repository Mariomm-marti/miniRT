/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 02:24:54 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/28 04:12:44 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

int			main(int argc, char **argv)
{
	t_light	*light;
	t_conf	config;

	ft_bzero(&config, sizeof(t_conf));
	if (!(create_light(&config, *(argv + 1))))
	{
		printf("ERROR CREATING LIGHT");
		print_error();
		system("leaks a.out");
		return (1);
	}
	if ((light = get_light(&config, 100)))
	{
		printf("Shouldnt be printed bc error handling");
		print_error();
		free_lights(&config);
		return (1);
	}
	light = get_light(&config, 0);
	if (g_errno)
	{
		print_error();
		free_lights(&config);
		system("leaks a.out");
		return (1);
	}
	printf("LIGHT:\n");
	printf("LOC X %f - Y %f - Z %f\n", light->loc.x, light->loc.y, light->loc.z);
	printf("RATIO %f\n", light->ratio);
	printf("COLOR %.6X\n", light->color);
	printf("NEXT PTR %p\n", light->next);
	return (0);
}
