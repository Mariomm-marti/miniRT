/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_triangles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:49:41 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/30 21:55:07 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>
#include <stdlib.h>

int			main(int argc, char **argv)
{
	t_triangle	*tr;
	t_conf		conf;

	ft_bzero(&conf, sizeof(t_conf));
	if (!(tr = create_triangle(&conf, *(argv + 1))))
	{
		printf("ERROR CREATING TRIANGLE!\n");
		print_error();
		system("leaks a.out");
		return (1);
	}
	if (get_triangle(&conf, 100))
	{
		printf("Shouldnt be printed bc error handling");
		print_error();
		system("leaks a.out");
		return (1);
	}
	tr = get_triangle(&conf, 0);
	if (g_errno)
	{
		print_error();
		free_triangles(&conf);
		system("leaks a.out");
		return (1);
	}
	printf("CYL:\n");
	printf("LOC A: X %f - Y %f - Z %f\n", tr->a.x, tr->a.y, tr->a.z);
	printf("LOC B: X %f - Y %f - Z %f\n", tr->b.x, tr->b.y, tr->b.z);
	printf("LOC C: X %f - Y %f - Z %f\n", tr->c.x, tr->c.y, tr->c.z);
	printf("COLOR: #%.6X\n", tr->color);
	printf("NEXT PTR: %p\n", tr->next);
	system("leaks a.out");
	return (0);
}
