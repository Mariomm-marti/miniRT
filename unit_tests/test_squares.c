/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_squares.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 22:43:38 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/29 22:50:56 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>
#include <stdlib.h>

int			main(int argc, char **argv)
{
	t_square	*square;
	t_conf		config;

	ft_bzero(&config, sizeof(t_conf));
	if (!(create_square(&config, *(argv + 1))))
	{
		printf("ERROR CREATING SQUARE!\n");
		print_error();
		system("leaks a.out");
		return (1);
	}
	if ((square = get_square(&config, 100)))
	{
		printf("Shouldnt be printed bc error handling");
		print_error();
		system("leaks a.out");
		return (1);
	}
	square = get_square(&config, 0);
	if (g_errno)
	{
		print_error();
		free_squares(&config);
		system("leaks a.out");
		return (1);
	}
	printf("SQUARE:\n");
	printf("LOC: X %f - Y %f - Z %f\n", square->loc.x, square->loc.y, square->loc.z);
	printf("DIR: X %f - Y %f - Z %f\n", square->dir.x, square->dir.y, square->dir.z);
	printf("SIDE SIZE: %f\n", square->side_size);
	printf("COLOR: #%.6X\n", square->color);
	printf("NEXT PTR: %p\n", square->next);
	system("leaks a.out");
	return (0);
}
