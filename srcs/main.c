/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:18:44 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/27 16:25:36 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>
#include <libft.h>
#include <mlx.h>

static int	validate_args(int argc, char **argv)
{
	char	*dptr;

	if (argc != 2 && argc != 3)
		g_errno = EXEC_INV_ARG;
	else if (!(dptr = ft_strrchr(*(argv + 1), '.')) || ft_strcmp(".rt", dptr))
		g_errno = EXEC_INV_FNAME;
	else if (argc == 3 && ft_strcmp("--save", *(argv + 2)))
		g_errno = EXEC_INV_ARG;
	return (!g_errno);
}

int			main(int argc, char **argv)
{
	t_conf	conf;
	void	*mlxptr;
	void	*mlxwin;

	ft_bzero(&conf, sizeof(t_conf));
	if (!validate_args(argc, argv) || !(mlxptr = mlx_init()))
	{
		print_error();
		return (0);
	}
	if (!read_config(&conf, *(argv + 1), mlxptr) || g_errno)
	{
		print_error();
		terminate_program(&conf, mlxptr);
	}
	if (!(mlxwin = mlx_new_window(mlxptr, conf.r.x, conf.r.y, "miniRT")))
		terminate_program(&conf, mlxptr);
	render_cameras(conf.c, &conf);
	mlx_put_image_to_window(mlxptr, mlxwin, conf.c->img, 0, 0);
	mlx_loop(mlxptr);
	terminate_program(&conf, mlxptr);
}
