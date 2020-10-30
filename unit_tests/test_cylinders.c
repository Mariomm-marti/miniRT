/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cylinders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:05:26 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/30 21:18:25 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>
#include <stdlib.h>

int			main(int argc, char **argv)
{
	t_cylinder	*cyl;
	t_conf		conf;

	ft_bzero(&conf, sizeof(t_conf));
	if (!(cyl = create_cylinder(&conf, *(argv + 1))))
	{
		printf("ERROR CREATING CYLINDER!\n");
		print_error();
		system("leaks a.out");
		return (1);
	}
	if (get_cylinder(&conf, 100))
	{
		printf("Shouldnt be printed bc error handling");
		print_error();
		system("leaks a.out");
		return (1);
	}
	cyl = get_cylinder(&conf, 0);
	if (g_errno)
	{
		print_error();
		free_cylinders(&conf);
		system("leaks a.out");
		return (1);
	}
	printf("CYL:\n");
	printf("LOC: X %f - Y %f - Z %f\n", cyl->loc.x, cyl->loc.y, cyl->loc.z);
	printf("DIR: X %f - Y %f - Z %f\n", cyl->dir.x, cyl->dir.y, cyl->dir.z);
	printf("DIAM: %f\n", cyl->diameter);
	printf("HEIGHT: %f\n", cyl->height);
	printf("COLOR: #%.6X\n", cyl->color);
	printf("NEXT PTR: %p\n", cyl->next);
	system("leaks a.out");
	return (0);
}
