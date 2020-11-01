/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_read_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:56:07 by mmartin-          #+#    #+#             */
/*   Updated: 2020/11/01 22:25:05 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <mlx.h>

int		main(int argc, char **argv)
{
	t_conf	conf;
	void	*mlx_ptr;

	ft_bzero(&conf, sizeof(t_conf));
	if (!(mlx_ptr = mlx_init()))
		return (1);
	if (!read_config(&conf, *(argv + 1), mlx_ptr))
		return (1);
	if (g_errno)
	{
		print_error();
		terminate_program(&conf, mlx_ptr);
		return (1);
	}
	printf("EVERYTHING WENT OK\n");
	terminate_program(&conf, mlx_ptr);
	return (0);
}
