/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:45:05 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/24 17:45:10 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h> // delet
#include "../includes/minirt.h"

int			main(int argc, char **argv)
{
	t_conf		config;
	t_errcode	error;

	if (argc != 2)
		return (1);
	ft_bzero(&config, sizeof(t_conf));
	//if ((error = read_conf(&config, argv[1])))
	//{
	//	print_error(error);
	//}
	read_amb(&config, argv[1]);
	printf("----------------\n");
	printf("RESOLUTION\n");
	printf("X: %d\nY: %d\n", config.res.x, config.res.y);
	printf("----------------\n");
	printf("AMBIENT\n");
	printf("RATIO: %f\nCOLOR: #%06X\n", config.amb.ratio, config.amb.color);
	printf("----------------\n");
}
