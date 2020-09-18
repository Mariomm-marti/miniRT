/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:45:05 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/18 20:29:39 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "../includes/minirt.h"

int			main(int argc, char **argv)
{
	t_conf	conf;

	if (argc != 2)
		return (1);
	ft_bzero(&conf, sizeof(t_conf));
	print_error(read_res(&conf, &argv[1][1]));
	printf("ERROR CODE\n\n%d\nWIDTH\n\n%d\nHEIGHT\n\n", conf.res.x, conf.res.y);
}
